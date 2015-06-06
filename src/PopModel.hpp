/*
 * GeneralModel.hpp
 *
 *  Created on: Nov 9, 2014
 *      Author: young
 */

#ifndef POPMODEL_HPP_
#define POPMODEL_HPP_

#include <string>
#include <vector>
#include "Population.hpp"

class PopModel
{
private:
	std::vector<int> nhaps;
	std::vector<int> nes;
	std::vector<std::vector<double> > props;
	Population pop;
	bool isValidNhap() const;
	bool isValidNe() const;
	bool isValidProp() const;
public:
	PopModel(const std::string & file);
	virtual ~PopModel();
	int getT() const;
	int getK() const;
	std::vector<int> getNhaps() const;
	Population getPop() const;
	void evolve(double len);
};

#endif /* POPMODEL_HPP_ */
