/*
 * Chrom.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: xiong_yang
 */

#include <iostream>
#include "Chrom.hpp"
using namespace std;
Chrom::Chrom()
{
	std::vector<Segment> segments;
	this->segments = segments;
	std::vector<double> breaks;
	this->breaks = breaks;
}

Chrom::Chrom(const std::vector<Segment> & segments) :
		segments(segments)
{
	std::vector<double> breaks;
	for (size_t i = 0; i < segments.size(); ++i)
	{
		breaks.push_back(segments.at(i).getEnd());
	}
	if (breaks.size() > 0)
	{
		breaks.pop_back();
	}
	this->breaks = breaks;
}

Chrom::~Chrom()
{
// TODO Auto-generated destructor stub
}

double Chrom::getLength() const
{
	return segments.back().getEnd();
}

int Chrom::getNumSegments() const
{
	return static_cast<int>(segments.size());
}

int Chrom::indexOf(double pos) const
{
	int left = 0;
	int right = static_cast<int>(breaks.size());
	if (breaks.size() == 0)
		return 0;
	else
	{
		if (pos > breaks.back())
		{
			return right;
		}
		if (pos <= breaks.front())
		{
			return 0;
		}

		int mid = (left + right + 1) / 2;
		while (left < right)
		{
			if (pos > breaks.at(mid))
				left = mid;
			else
				right = mid - 1;
			mid = (left + right + 1) / 2;
		}
		return left + 1;
	}
}

void Chrom::addSegment(Segment & segment)
{
	if (segments.size() > 0)
	{
		if (segment.getStart() != segments.back().getEnd())
		{
			std::cerr << "There is a gap between newly added segment and the end of chromosome, segment shifted" << std::endl;
			//shift the segment
			double prevEnd = segments.back().getEnd();
			segment.setEnd(prevEnd + segment.getLength());
			segment.setStart(prevEnd);
		}
		//cout << segment.getEnd() << endl;
		breaks.push_back(segment.getEnd());
	}
	segments.push_back(segment);
}

void Chrom::smooth()
{
	std::vector<Segment> tmpSegments;
	Segment seg1 = segments.front();
	for (size_t i = 1; i < segments.size(); ++i)
	{
		Segment seg2 = segments.at(i);
		//if adjacent segments have the same label, merge it
		if (seg1.getLabel() / 10000 == seg2.getLabel() / 10000)
		{
			seg1.setEnd(seg2.getEnd());
		}
		else
		{
			//different label, then add segment to segments
			//and assign segment 2 to segment 1
			tmpSegments.push_back(seg1);
			seg1 = seg2;
		}
	}
	tmpSegments.push_back(seg1);
	segments = tmpSegments;
	updateBreaks();
}

void Chrom::updateBreaks()
{
	std::vector<double> tmp;
	for (size_t i = 0; i < segments.size(); ++i)
	{
		tmp.push_back(segments.at(i).getEnd());
	}
	if (tmp.size() > 0)
	{
		tmp.pop_back();
	}
	breaks = tmp;
}

Segment Chrom::getSegment(int index) const
{
	return segments.at(index);
}

std::vector<Segment> Chrom::extSegment(double start, double end) const
{
	std::vector<Segment> extSegs;
	int startIndex = indexOf(start);
	int endIndex = indexOf(end);
	// if the start position is on the end of a segment, then move to next
	if (start == segments.at(startIndex).getEnd())
		startIndex++;
	Segment ss = segments.at(startIndex);
	// if the start and end positions are on the same segment, then cut part of it
	if (startIndex == endIndex)
	{
		Segment seg = Segment(start, end, ss.getLabel());
		extSegs.push_back(seg);
	}
	else
	{
		Segment seg = Segment(start, ss.getEnd(), ss.getLabel());
		extSegs.push_back(seg);
		for (int i = startIndex + 1; i < endIndex; i++)
		{
			extSegs.push_back(segments.at(i));
		}
		Segment se = segments.at(endIndex);
		seg = Segment(se.getStart(), end, se.getLabel());
		extSegs.push_back(seg);
	}
	return extSegs;
}

void Chrom::print() const
{
	int i;
	int nseg = getNumSegments();
	for (i = 0; i < nseg; ++i)
	{
		Segment seg = getSegment(i);
		std::cout << seg.getStart() << "\t" << seg.getEnd() << "\t" << seg.getLabel() << std::endl;
	}
}

std::ostream & operator<<(std::ostream & os, const Chrom & chr)
{
	int nseg = chr.getNumSegments();
	for (int i = 0; i < nseg; ++i)
	{
		Segment seg = chr.getSegment(i);
		os << seg.getStart() << "\t" << seg.getEnd() << "\t" << seg.getLabel() << std::endl;
	}
	return os;
}
//test case
//int main() {
//	vector<Segment> segs;
//	segs.push_back(Segment(0.0, 0.2, 10001));
//	segs.push_back(Segment(0.2, 0.8, 10000));
//	segs.push_back(Segment(0.8, 1.0, 20002));
//	segs.push_back(Segment(1.0, 1.25, 20003));
//	segs.push_back(Segment(1.25, 1.5, 10000));
//	Chrom chr(segs);
//	Segment ss(1.6, 1.8, 10003);
//	chr.addSegment(ss);
//	//size_t i;
//	cout << "before smooth, the num is: " << chr.getNumSegments() << endl;
//	cout << chr;
//	//chr.print();
//	chr.smooth();
//	cout << "after smooth, the num is: " << chr.getNumSegments() << endl;
//	//chr.print();
//	cout << chr;
//	//chr.getSegment(1);
//}

