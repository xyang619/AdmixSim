/*
 * Population.h
 *
 *  Created on: Sep 28, 2014
 *      Author: xiong_yang
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include "Chrom.h"

class Population
{
private:
	std::vector<Chrom> chrs;
public:
	Population();
	Population(const std::vector<Chrom> & chrs);
	virtual ~Population();
	std::vector<Chrom> getChrs() const;
	Population & addChr(Chrom & chr);
	Population & evolve(int ne);
	std::vector<Chrom> sample(int nsamp) const;
	std::vector<Population> split(double prop);
};

#endif /* POPULATION_H_ */
