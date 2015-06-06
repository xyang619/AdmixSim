/*
 * Segment.hpp
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#ifndef SEGMENT_HPP_
#define SEGMENT_HPP_

class Segment
{
private:
	double start;
	double end;
	int label;
public:
	Segment();
	Segment(double start, double end, int label);
	virtual ~Segment();
	double getStart() const;
	double getEnd() const;
	int getLabel() const;
	double getLength() const;
	void setStart(double start);
	void setEnd(double end);
	void setLabel(int label);
};

#endif /* SEGMENT_HPP_ */
