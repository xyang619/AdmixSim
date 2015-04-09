/*
 * Segment.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#include "Segment.h"

Segment::Segment() :
		start(0), end(0), label(1)
{
}

Segment::Segment(double start, double end, int label) :
		start(start), end(end), label(label)
{
}

Segment::~Segment()
{
	// TODO Auto-generated destructor stub
}
double Segment::getStart() const
{
	return start;
}

double Segment::getEnd() const
{
	return end;
}

int Segment::getLabel() const
{
	return label;
}

double Segment::getLength() const
{
	return end - start;
}

void Segment::setStart(double start)
{
	this->start = start;
}

void Segment::setEnd(double end)
{
	this->end = end;
}

void Segment::setLabel(int label)
{
	this->label = label;
}

