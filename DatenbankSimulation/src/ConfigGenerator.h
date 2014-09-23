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

namespace HDDTest {

enum mode_readMode { LEFT_TO_RIGHT, RM_RANDOM};
enum mode_extendDistribution {ED_CONSTANT , ED_RANDOM};

struct startSize {
	unsigned long long int start;
	unsigned long long int size;
};

class ConfigGenerator {
	unsigned long long int size_start;
	unsigned long long int size_spread;
	unsigned long long int size_relation;
	unsigned long long int size_extends;
	enum mode_readMode readMode;
	enum mode_extendDistribution extendDistribution;

	std::vector<struct startSize> readOrder; // marks start and size of what is read (in kb)
public:
	ConfigGenerator(unsigned long long int size_start, unsigned long long int size_spread, unsigned long long int size_relation, unsigned long long int size_extends, enum mode_readMode readMode, enum mode_extendDistribution extendDistribution);
	void generate();
	~ConfigGenerator();
};

} /* namespace HDDTest */
#endif /* CONFIGGENERATOR_H_ */
