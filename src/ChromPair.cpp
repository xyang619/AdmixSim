/*
 * ChromPair.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "ChromPair.hpp"

ChromPair::ChromPair()
{
	Chrom chr1, chr2;
	chrom1 = chr1;
	chrom2 = chr2;
}

ChromPair::ChromPair(const Chrom & chrom1, const Chrom & chrom2) :
		chrom1(chrom1), chrom2(chrom2)
{
}

ChromPair::~ChromPair()
{
	// TODO Auto-generated destructor stub
}

Chrom ChromPair::getChrom(int index) const
{
	if (index == 1)
	{
		return chrom1;
	}
	else
	{
		return chrom2;
	}
}

//double ChromPair::waitTime() {
//	double lambda = chrom1.getLength();
//	//srand(time(NULL));
//	double prob = (rand() * 1.0) / RAND_MAX;
//	double wTime = -log(1 - prob) / lambda;
//	//cout << "prob:" << prob << ";wTime" << wTime << endl;
//	return wTime;
//}

int ChromPair::getPoissonNumb(double lambda) const
{
	double length = exp(-lambda);
	double prob = 1.0;
	int numb = 0;
	do
	{
		numb++;
		prob *= rand() * 1.0 / RAND_MAX;
	} while (prob > length);
	return numb - 1;
}

void ChromPair::breakPoints(double * breaks, int n) const
{
	double length = chrom1.getLength();
	breaks[0] = 0.0;
	for (int i = 1; i < n - 1; ++i)
	{
		breaks[i] = rand() * length / RAND_MAX;
	}
	breaks[n - 1] = length;
	std::sort(breaks, breaks + n);
}

//void ChromPair::sort(double breaks[], int n) {
//	int iMin;
//	for (int i = 0; i < n - 1; ++i) {
//		iMin = i;
//		for (int j = i + 1; j < n; ++j) {
//			if (breaks[j] < breaks[iMin]) {
//				iMin = j;
//			}
//		}
//		if (iMin != i) {
//			double tmp = breaks[iMin];
//			breaks[i] = breaks[iMin];
//			breaks[iMin] = tmp;
//		}
//	}
//}

ChromPair & ChromPair::recombine()
{
	if (chrom1.getLength() != chrom2.getLength())
	{
		std::cerr << "Chromosome length differ, please check again" << std::endl;
		return *this;
	}
	else
	{
		int numb = getPoissonNumb(chrom1.getLength()) + 2;
		double bps[numb];
		breakPoints(bps, numb);
		std::vector<Segment> ss1;
		std::vector<Segment> ss2;
		double start = bps[0];
		for (int i = 1; i < numb; ++i)
		{
			double end = bps[i];
			if (i % 2)
			{
				std::vector<Segment> tmps = chrom1.extSegment(start, end);
				for (size_t j = 0; j < tmps.size(); ++j)
				{
					ss1.push_back(tmps.at(j));
				}
				tmps = chrom2.extSegment(start, end);
				for (size_t j = 0; j < tmps.size(); ++j)
				{
					ss2.push_back(tmps.at(j));
				}
			}
			else
			{
				std::vector<Segment> tmps = chrom2.extSegment(start, end);
				for (size_t j = 0; j < tmps.size(); ++j)
				{
					ss1.push_back(tmps.at(j));
				}
				tmps = chrom1.extSegment(start, end);
				for (size_t j = 0; j < tmps.size(); ++j)
				{
					ss2.push_back(tmps.at(j));
				}
			}
			start = end;
		}
		Chrom chr1(ss1);
		Chrom chr2(ss2);
		chrom1 = chr1;
		chrom2 = chr2;
		return *this;
	}
}

//int main()
//{
//	srand(time(0));
//	std::vector<Segment> segs;
//	segs.push_back(Segment(0, 2, 1));
//	Chrom chr1(segs);
//	std::vector<Segment> segs2;
//	segs2.push_back(Segment(0, 2, 2));
//	Chrom chr2(segs2);
//	ChromPair cp = ChromPair(chr1, chr2);
//	for (int i = 0; i < 5; ++i)
//	{
//		std::cout << "generation " << i + 1 << std::endl;
//		cp.recombine();
//		cp.getChrom(1).print();
//		//cp.getChrom(2).print();
//	}
//}

