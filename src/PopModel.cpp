/*
 * PopModel.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: young
 */

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ChromPair.hpp"
#include "PopModel.hpp"

using namespace std;

PopModel::PopModel(const string &file)
{
	ifstream fin(file.c_str());
	if (!fin.good())
	{
		cout << "Can't open model file " << file << endl;
		exit(1);
	}
	//vector<int> nhaps;
	//vector<int> nes;
	//vector<vector<double> > props;
	bool ancSet = false;
	bool isStart = false;
	string line;
	while (getline(fin, line))
	{
		//pure comments
		if (line.size() > 0 && line.at(0) == '#')
		{
			continue;
		}
		//remove comments
		size_t pos = line.find('#');
		if (pos != string::npos)
		{
			line = line.substr(0, pos);
		}
		//check for the start point of population size and proportion
		if (line.substr(0, 2) == "//")
		{
			isStart = true;
			continue;
		}
		if (isStart && !ancSet)
		{
			cerr << "Uninitialized number of ancestral population haplotypes" << endl;
			fin.close();
			exit(1);
		}
		istringstream iss(line);
		if (!isStart && iss)
		{
			int nhap;
			while (iss >> nhap)
			{
				nhaps.push_back(nhap);
			}
			ancSet = true;
		}
		else if (isStart && iss)
		{
			int ne;
			iss >> ne;
			nes.push_back(ne);
			double prop;
			vector<double> prop_rows;
			while (iss >> prop)
			{
				prop_rows.push_back(prop);
			}
			props.push_back(prop_rows);
		}
	}

	fin.close();
	//this->nhaps = nhaps;
	//this->nes = nes;
	//this->props = props;
	if (isValidNhap() && isValidNe() && isValidProp())
	{
		pop = Population();
	}
	else
	{
		exit(1);
	}
}

PopModel::~PopModel()
{
}

bool PopModel::isValidNhap() const
{
	int K = getK();
	for (int i = 0; i < K; ++i)
	{
		if (nhaps.at(i) <= 0)
		{
			cerr << "Error: The size of ancestral haplotypes must be positive" << endl;
			return false;
		}
	}
	return true;
}

bool PopModel::isValidNe() const
{
	int T = getT();
	for (int i = 0; i < T; ++i)
	{
		if (nes.at(i) <= 0)
		{
			cerr << "Error: Population size must be positive" << endl;
			return false;
		}
	}
	return true;
}

bool PopModel::isValidProp() const
{
	int K = getK();
	int T = getT();
	for (int i = 0; i < T; ++i)
	{
        int tempK = props.at(i).size();
        if (tempK != K)
        {
            cerr << "Error: The number of ancestral contributions at generation " << i << " differ from the number of ancestral populations" << endl;
            return false;
        }
		double tsum = 0;
		for (int j = 0; j < K; ++j)
		{
			double prop = props.at(i).at(j);
			if (prop < 0 || prop > 1.0)
			{
				cerr << "Error: Admixture proportion must be between 0 and 1" << endl;
				return false;
			}
			tsum += prop;
		}

		if (i == 0 && abs(tsum - 1.0) > 1e-12)
		{
			cerr << "Error: The admixture proportion of initial generation must sum to 1" << endl;
			return false;
		}
		if (tsum - 1.0 > 1e-12)
		{
			cerr << "Error: The sum of admixture proportion in generation " << i + 1 << " is larger than 1" << endl;
			return false;
		}
	}
	return true;
}
int PopModel::getT() const
{
	int T = static_cast<int>(nes.size());
	return T;
}

int PopModel::getK() const
{
	int K = static_cast<int>(nhaps.size());
	return K;
}

vector<int> PopModel::getNhaps() const
{
	return nhaps;
}

Population PopModel::getPop() const
{
	return pop;
}

void PopModel::evolve(double len)
{
	int K = getK();
	int T = getT();
	for (int i = 0; i < T; ++i)
	{
		int numbHapsPrev = 0; //number of haplotypes should sampled from previous generation
		int curNumbHaps = nes.at(i) * 2; //number of haplotypes
		int numbHaps[K];
		int sumNumbHaps = 0;
		for (int j = 0; j < K; ++j)
		{
			numbHaps[j] = (int) (curNumbHaps * props.at(i).at(j));
			sumNumbHaps += numbHaps[j];
		}
		// prepare individuals in current generation
		numbHapsPrev = curNumbHaps - sumNumbHaps;
		std::vector<Chrom> hapsCur;
		if (numbHapsPrev > 0)
		{
			hapsCur = pop.sample(numbHapsPrev);
		}
		for (int j = 0; j < K; j++)
		{
			if (numbHaps[j] > 0)
			{
				for (int k = 0; k < numbHaps[j]; k++)
				{
					std::vector<Segment> segs;
                    //modified to support at max 999999 ancestral haplotypes per ancestral population
					int lab = (j + 1) * 1000000 + rand() % nhaps.at(j);
					segs.push_back(Segment(0, len, lab));
					Chrom chr1(segs);
					hapsCur.push_back(chr1);
				}
			}
		}
		Population tmpPop(hapsCur);
		tmpPop.evolve(nes.at(i));
		pop = tmpPop;
	}
}

