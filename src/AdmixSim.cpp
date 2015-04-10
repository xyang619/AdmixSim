/*
 * AdmixSim.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: young
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <cstdlib>
#include "Param.h"
#include "PopModel.h"
#include "Utils.h"

using namespace std;

int main(int argc, char **argv)
{
	int nsample;
	double length;
	double pos;
	string modfile;
	string mapfile;
	string ancfile;
	string hapfile;
	string segfile;
	vector<double> poss;
	vector<Chrom> sample;
	map<int, vector<string> > anchaps;
	Param * par;
	PopModel * model;

	par = new Param(argc, argv);
	par->echo();
	nsample = par->getNSample();
	modfile = par->getModFile();
	length = par->getLength();
	mapfile = par->getMapFile();
	ancfile = par->getAncFile();
	hapfile = par->getOutPrefix() + ".hap";
	segfile = par->getOutPrefix() + ".seg";
	model = new PopModel(modfile);

	ifstream mfin(mapfile.c_str());
	if (!mfin.good())
	{
		cerr << "Can't open file " << mapfile << endl;
		abort();
	}
	while (mfin >> pos)
	{
		poss.push_back(pos);
	}
	mfin.close();

	ifstream hfin(ancfile.c_str());
	if (!hfin.good())
	{
		cerr << "Can't open file " << ancfile << endl;
		abort();
	}
	for (int j = 0; j < model->getK(); ++j)
	{
		vector<string> haps;
		anchaps[j + 1] = haps;
	}
	string line;
	int key = 1;
	int nInd = 0;
	int nAnc = model->getNhaps().at(key - 1);
	while (getline(hfin, line))
	{
		if (nInd < nAnc)
		{
			anchaps.at(key).push_back(line);
			++nInd;
		}
		else
		{
			++key;
			nInd = 0;
			nAnc = model->getNhaps().at(key - 1);
			anchaps.at(key).push_back(line);
			++nInd;
		}
	}
	hfin.close();

	model->evolve(length);
	sample = model->getPop().sample(nsample);

	//prepare output
	ofstream segout(segfile.c_str());
	ofstream hapout(hapfile.c_str());
	if (!segout.good() || !hapout.good())
	{
		cerr << "Can't open file " << segfile << " or " << hapfile << endl;
		abort();
	}
	//cout << "//admixed haplotypes" << endl;
	for (int i = 0; i < nsample; ++i)
	{
		Chrom chr = sample.at(i);
		int nseg = chr.getNumSegments();
		string outStr = "";
		for (int k = 0; k < nseg; ++k)
		{
			Segment seg = chr.getSegment(k);
			int key = seg.getLabel() / 10000;
			int index = seg.getLabel() % 10000;
			double start = seg.getStart();
			double end = seg.getEnd();
			outStr = outStr + copySeq(poss, anchaps.at(key).at(index), start, end);
		}
		hapout << outStr << endl;

		chr.smooth();
		nseg = chr.getNumSegments();
		for (int k = 0; k < nseg; ++k)
		{
			Segment seg = chr.getSegment(k);
			double start, end;
			int label;
			start = seg.getStart();
			end = seg.getEnd();
			label = seg.getLabel() / 10000;
			segout << setprecision(8) << setw(16) << start << setw(16) << end << setw(4) << label << endl;
		}

	}
	segout.close();
	hapout.close();
	return 0;
}

