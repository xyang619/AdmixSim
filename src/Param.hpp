/*
 * Param.hpp
 *
 *  Created on: Apr 7, 2015
 *      Author: young
 */

#ifndef PARAM_HPP_
#define PARAM_HPP_

#include <string>
const std::string kProgram = "AdmixSim";
const std::string kVersion = "1.0.3";

class Param
{
public:
	Param(int argc, char ** argv);
	virtual ~Param();
	void echo();
	int getNSample() const;
	double getLength() const;
	std::string getModfile() const;
	std::string getInput() const;
	std::string getOutput() const;
private:
	int nsample;
	unsigned long seed;
	double length;
	std::string modfile;
	std::string input;
	std::string output;
	void help();

};

#endif /* PARAM_HPP_ */
