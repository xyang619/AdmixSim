/*
 * Chrom.hpp
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#ifndef CHROM_HPP_
#define CHROM_HPP_

#include <vector>
#include <iostream>
#include "Segment.hpp"

class Chrom
{
private:
	std::vector<Segment> segments;
	std::vector<double> breaks;
	void updateBreaks();
public:
	Chrom();
	Chrom(const std::vector<Segment> &segments);
	virtual ~Chrom();
	double getLength() const;
	int getNumSegments() const;
	int indexOf(double pos) const;
	void addSegment(Segment &segment);
	std::vector<Segment> extSegment(double start, double end) const;
	void smooth();
	Segment getSegment(int index) const;
	//void print() const;
    friend std::ostream & operator<<(std::ostream &os, const Chrom &chrom);
};

#endif /* CHROM_HPP_ */
