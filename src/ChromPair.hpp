/*
 * ChromPair.hpp
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#ifndef CHROMPAIR_HPP_
#define CHROMPAIR_HPP_

#include "Chrom.hpp"

class ChromPair
{
private:
	Chrom chrom1;
	Chrom chrom2;
	int getPoissonNumb(double lambda) const;
	void breakPoints(double * breaks, int n) const;
public:
	ChromPair();
	ChromPair(const Chrom & chrom1, const Chrom & chrom2);
	virtual ~ChromPair();
	Chrom getChrom(int index) const;
	//double waitTime();
	//void sort(double[], int);
	ChromPair & recombine();
};

#endif /* CHROMPAIR_HPP_ */
