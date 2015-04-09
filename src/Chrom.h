/*
 * Chrom.h
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#ifndef CHROM_H_
#define CHROM_H_

#include <vector>
#include <iostream>
#include "Segment.h"

class Chrom
{
private:
	std::vector<Segment> segments;
	std::vector<double> breaks;
	void updateBreaks();
public:
	Chrom();
	Chrom(const std::vector<Segment> & segments);
	virtual ~Chrom();
	double getLength() const;
	int getNumSegments() const;
	int indexOf(double pos) const;
	void addSegment(Segment & segment);
	std::vector<Segment> extSegment(double start, double end) const;
	void smooth();
	Segment getSegment(int index) const;
	void print() const;
};

#endif /* CHROM_H_ */
