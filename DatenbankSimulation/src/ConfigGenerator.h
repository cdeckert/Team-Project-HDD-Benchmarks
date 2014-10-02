/*
 * ConfigGenerator.h
 *
 *  Created on: 23.09.2014
 *      Author: chris
 */

#ifndef CONFIGGENERATOR_H_
#define CONFIGGENERATOR_H_

#include <vector>
#include <stdlib.h>
#include "stdio.h"
#include <iostream>
#include <string>

namespace HDDTest
{

enum mode_readMode {LEFT_TO_RIGHT, RM_RANDOM};
enum mode_extentDistribution {ED_CONSTANT , ED_RANDOM};

struct startSize
{
	unsigned long long int start; // in KB
	unsigned long long int size; // in KB
};

class ConfigGenerator
{
private:
	// start of relations
	unsigned long long int size_start;
	// spreading of a single relation
	unsigned long long int size_spread;
	// size of a relation
	unsigned long long int size_relation;
	// extent size
	unsigned long long int size_extents;
	enum mode_readMode readMode;
	enum mode_extentDistribution extentDistribution;

	std::vector<struct startSize> readOrder; // marks start and size of what is read (in kb)
	void init_rand();

public:
	ConfigGenerator(unsigned long long int size_start, unsigned long long int size_spread,
					unsigned long long int size_relation, unsigned long long int size_extents,
					enum mode_readMode readMode, enum mode_extentDistribution extentDistribution);
	~ConfigGenerator();

	void generate();
	std::vector<struct startSize> getReadOrder() const;
	unsigned long long int getSizeExtents() const;
	unsigned long long int getSizeStart() const;
	void setSizeStart(unsigned long long int sizeStart);
	std::string configToString();
};

} /* namespace HDDTest */
#endif /* CONFIGGENERATOR_H_ */
