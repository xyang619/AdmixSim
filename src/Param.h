/*
 * Param.h
 *
 *  Created on: Apr 7, 2015
 *      Author: young
 */

#ifndef PARAM_H_
#define PARAM_H_

#include <string>

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

#endif /* PARAM_H_ */
