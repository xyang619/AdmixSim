/*
 * Utils.hpp
 *
 *  Created on: Apr 7, 2015
 *      Author: young
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>
#include<string>

int findPos(const std::vector<double> & poss, double pos);
std::string copySeq(const std::vector<double> & poss, const std::string & seq, double start, double end);

#endif /*UTILS_HPP_*/
