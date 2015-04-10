/*
 * Param.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: young
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Param.h"

using namespace std;

Param::Param(int argc, char ** argv) :
		nsample(10), seed(0), length(1.0), modfile(""), mapfile(""), ancfile(""), outPrefix("output")
{
	if (argc > 1 && (string(argv[1]) == "-h" || string(argv[1]) == "--help"))
	{
		help();
		exit(0);
	}

	if (argc < 7)
	{
		cerr << "Need more arguments than provided, use -h/--help to get more help" << endl;
		exit(1);
	}
	bool givenSeed = 0;

	for (int i = 0; i < argc; ++i)
	{
		string arg(argv[i]);
		if (arg == "-h" || arg == "--help")
		{
			help();
			exit(0);
		}
		else if (arg == "-f" || arg == "--file")
		{
			modfile = string(argv[++i]);
		}
		else if (arg == "-l" || arg == "--length")
		{
			length = atof(argv[++i]);
		}
		else if (arg == "-n" || arg == "--nsample")
		{
			nsample = atoi(argv[++i]);
		}
		else if (arg == "-m" || arg == "--map")
		{
			mapfile = string(argv[++i]);
		}
		else if (arg == "-a" || arg == "--anchap")
		{
			ancfile = string(argv[++i]);
		}
		else if (arg == "-o" || arg == "--output")
		{
			outPrefix = string(argv[++i]);
		}
		else if (arg == "-s" || arg == "--seed")
		{
			seed = unsigned(atol(argv[++i]));
			givenSeed = 1;
		}
	}

	if (modfile.size() == 0)
	{
		cerr << "Model description file must be specified" << endl;
		abort();
	}
	if (mapfile.size() == 0)
	{
		cerr << "Map file must be specified" << endl;
		abort();
	}
	if (ancfile.size() == 0)
	{
		cerr << "Ancestral haplotype file must be specified" << endl;
		abort();
	}
	if (outPrefix.size() == 0)
	{
		cerr << "Warning, output prefix using default" << endl;
		outPrefix = "output";
	}
	if (!givenSeed)
	{
		seed = unsigned(time(0));
	}
	srand(seed);

}

Param::~Param()
{
	// TODO Auto-generated destructor stub
}

void Param::help()
{
	cout << "==============================================================================" << endl;
	cout << "AdmixSim v1.0.3" << endl;
	cout << "AdmixSim is designed to simulate data for admixed population under various and complex scenarios." << endl;
	cout << "Arguments:" << endl;
	cout << "\t-h/--help\tprint help message[optional]" << endl;
	cout << "\t-f/--file\tmodel description file [required]" << endl;
	cout << "\t-m/--map\tmapfile for the loci [required]" << endl;
	cout << "\t-a/--anchap\tcombined ancestral haplotype file [required]" << endl;
	cout << "\t-l/--length\tlength of chromosome simulated [optional, default=1]" << endl;
	cout << "\t-n/--nsample\tnumber of individuals sampled [optional, default=10]" << endl;
	cout << "\t-o/--output\tprefix of output files [optional, default=output]" << endl;
	cout << "\t-s/--seed\tseed of random generator [optional, default=time]" << endl;
	cout << "==============================================================================" << endl;

}

void Param::echo()
{
	cout << "==============================================================================" << endl;
	cout << "Arguments summary:" << endl;
	cout << "chromosome length: " << length << endl;
	cout << "number of samples: " << nsample << endl;
	cout << "model file: " << modfile << endl;
	cout << "map file: " << mapfile << endl;
	cout << "anchap file: " << ancfile << endl;
	cout << "output prefix: " << outPrefix << endl;
	cout << "random seed: " << seed << endl;
	cout << "==============================================================================" << endl;
}

int Param::getNSample() const
{
	return nsample;
}

double Param::getLength() const
{
	return length;
}

string Param::getModFile() const
{
	return modfile;
}

string Param::getMapFile() const
{
	return mapfile;
}

string Param::getAncFile() const
{
	return ancfile;
}

string Param::getOutPrefix() const
{
	return outPrefix;
}

