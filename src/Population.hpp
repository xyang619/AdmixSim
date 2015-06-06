/*
 * Population.hpp
 *
 *  Created on: Sep 28, 2014
 *      Author: xiong_yang
 */

#ifndef POPULATION_HPP_
#define POPULATION_HPP_

#include "Chrom.hpp"

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

#endif /* POPULATION_HPP_ */
