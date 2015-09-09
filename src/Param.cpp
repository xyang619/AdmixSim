/*
 * Param.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: young
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Param.hpp"

using namespace std;

Param::Param(int argc, char ** argv) :
		nsample(10), seed(0), length(1.0), modfile(""), mapfile(""), hapfile(""), output("output")
{
	if (argc > 1 && (string(argv[1]) == "-h" || string(argv[1]) == "--help"))
	{
		help();
		exit(0);
	}

	if (argc < 5)
	{
		cerr << "Need more arguments than provided, use -h/--help to get more help" << endl;
		exit(1);
	}
	bool givenSeed = false;

	for (int i = 0; i < argc; ++i)
	{
		string arg(argv[i]);
		if (arg == "-h" || arg == "--help")
		{
			help();
			exit(0);
		}
		else if (arg == "-m" || arg == "--modfile")
		{
			modfile = string(argv[++i]);
		}
		else if (arg == "-l" || arg == "--length")
		{
			length = atof(argv[++i]);
		}
		else if (arg == "-n" || arg == "--sample")
		{
			nsample = atoi(argv[++i]);
		}
		else if (arg == "-iM" || arg == "--mapfile")
		{
			mapfile = string(argv[++i]);
		}
		else if (arg == "-iH" || arg == "--hapfile")
		{
			hapfile = string(argv[++i]);
		}
		else if (arg == "-o" || arg == "--output")
		{
			output = string(argv[++i]);
		}
		else if (arg == "-s" || arg == "--seed")
		{
			seed = unsigned(atol(argv[++i]));
			givenSeed = true;
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
	if (hapfile.size() == 0)
	{
		cerr << "Anchap file must be specified" << endl;
		abort();
	}
	if (output.size() == 0)
	{
		cerr << "Warning, output prefix using default" << endl;
		output = "output";
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
	cout << "---------------------------------------------------------" << endl;
	cout << kProgram << "v" << kVersion << endl;
	cout << kProgram << " is designed to simulate data for admixed population under various and complex scenarios." << endl;
	cout << "Arguments:" << endl;
	cout << "\t-m/--modfile\t<string>\tModel description file [required]" << endl;
	cout << "\t-iM/--mapfile\t<string>\tGenetic map file [required]" << endl;
	cout << "\t-iH/--hapfile\t<string>\tAncestral haplotype file [required]" << endl;
	cout << "\t-l/--length\t[double]\tLength of chromosome simulated [optional, default=1]" << endl;
	cout << "\t-n/--sample\t[integer]\tNumber of individuals sampled [optional, default=10]" << endl;
	cout << "\t-o/--output\t[string]\tPrefix of output files [optional, default=output]" << endl;
	cout << "\t-s/--seed\t[integer]\tSeed of random generator [optional, default=time]" << endl;
	cout << "Options" << endl;
	cout << "\t-h/--help\tPrint help message[optional]" << endl;
	cout << "---------------------------------------------------------" << endl;

}

void Param::echo()
{
	cout << "---------------------------------------------------------" << endl;
	cout << "Arguments summary:" << endl;
	cout << "chromosome length: " << length << endl;
	cout << "number of samples: " << nsample << endl;
	cout << "model file: " << modfile << endl;
	cout << "map file: " << mapfile << endl;
	cout << "anchap file: " << hapfile << endl;
	cout << "output prefix: " << output << endl;
	cout << "random seed: " << seed << endl;
	cout << "---------------------------------------------------------" << endl;
}

int Param::getNSample() const
{
	return nsample;
}

double Param::getLength() const
{
	return length;
}

string Param::getModfile() const
{
	return modfile;
}

string Param::getMapfile() const
{
	return mapfile;
}

string Param::getHapfile() const
{
	return hapfile;
}

string Param::getOutput() const
{
	return output;
}

