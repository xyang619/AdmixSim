/*
 * Utils.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: young
 */
#include "Utils.hpp"

using namespace std;

int findPos(const vector<double> &poss, double pos)
{
	int left = 0;
	int right = static_cast<int>(poss.size());
	if (pos <= poss.front())
		return left;
	if (pos >= poss.back())
		return right;
	int mid = (left + right + 1) / 2;
	while (left < right)
	{
		if (pos > poss.at(mid))
			left = mid;
		else
			right = mid - 1;
		mid = (left + right + 1) / 2;
	}
	return left + 1;
}

string copySeq(const vector<double> &poss, const string &seq, double start, double end)
{
	int left, right;
	left = findPos(poss, start);
	right = findPos(poss, end);
	return seq.substr(left, right - left);
}

