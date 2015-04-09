/*
 * Population.cpp
 *
 *  Created on: Sep 28, 2014
 *      Author: xiong_yang
 */

#include <cstdlib>
#include "ChromPair.h"
#include "Population.h"

Population::Population()
{
	std::vector<Chrom> chrs;
	this->chrs = chrs;
}

Population::Population(const std::vector<Chrom> & chrs) :
		chrs(chrs)
{
}

Population::~Population()
{
	// TODO Auto-generated destructor stub
}

std::vector<Chrom> Population::getChrs() const
{
	return chrs;
}

Population & Population::addChr(Chrom & chr)
{
	chrs.push_back(chr);
	return *this;
}

Population & Population::evolve(int nec)
{
	std::vector<Chrom> chrs_next;
	size_t size = chrs.size();
	for (int i = 0; i < nec; ++i)
	{
		int ind1, ind2;
		ind1 = rand() % size;
		ind2 = rand() % size;
		while (ind1 == ind2)
		{
			ind2 = rand() % size;
		}
		Chrom chr1 = chrs.at(ind1);
		Chrom chr2 = chrs.at(ind2);
		ChromPair cp(chr1, chr2);
		cp = cp.recombine();
		chrs_next.push_back(cp.getChrom(1));
		chrs_next.push_back(cp.getChrom(2));
	}
	this->chrs = chrs_next;
	return *this;
}

std::vector<Chrom> Population::sample(int nsamp) const
{
	int size = static_cast<int>(chrs.size());
	std::vector<Chrom> samp;
	for (int i = 0; i < nsamp; ++i)
	{
		samp.push_back(chrs.at(rand() % size));
	}
	return samp;
}

std::vector<Population> Population::split(double prop)
{
	std::vector<Chrom> indivs1;
	std::vector<Chrom> indivs2;
	int size = static_cast<int>(chrs.size());
	int size1 = static_cast<int>(size * prop);
	std::vector<int> index, index1;
	int i;
	for (i = 0; i < size; ++i)
	{
		index.push_back(i);
	}
	for (i = 0; i < size1; ++i)
	{
		int tmp = rand() % index.size();
		index1.push_back(index.at(tmp));
		index.erase(index.begin() + tmp);
	}
	for (i = 0; i < size1; ++i)
	{
		indivs1.push_back(chrs.at(index1.at(i)));
	}
	int ilen = static_cast<int>(index.size());
	for (i = 0; i < ilen; ++i)
	{
		indivs2.push_back(chrs.at(index.at(i)));
	}
	std::vector<Population> pops;
	Population pop1(indivs1);
	Population pop2(indivs2);
	pops.push_back(pop1);
	pops.push_back(pop2);
	return pops;
}

//
//int main()
//{
//	srand(time(NULL));
//	std::vector<Chrom> indivs;
//	std::vector<Segment> segs;
//	segs.push_back(Segment(0, 2, 1));
//	Chrom chr1(segs);
//	std::vector<Segment> segs2;
//	segs2.push_back(Segment(0, 2, 2));
//	Chrom chr2(segs2);
//	std::vector<Segment> segs3;
//	segs3.push_back(Segment(0, 2, 3));
//	Chrom chr3(segs3);
//	indivs.push_back(chr1);
//	indivs.push_back(chr2);
//	indivs.push_back(chr3);
//	Population p(indivs);
//	p.split(0.2);
//
//	for (int t = 0; t < 4; ++t)
//	{
//		std::cout << "===generation: " << t << std::endl;
//
//		std::vector<Chrom> sp = p.sample(3);
//		for (size_t i = 0; i < sp.size(); ++i)
//		{
//			std::cout << "##indiv: " << i + 1 << std::endl;
//			sp.at(i).print();
//		}
//		p.evolve(rand() % 100 + 50);
//	}
//}
