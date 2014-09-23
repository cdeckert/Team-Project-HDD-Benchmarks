/*
 * ConfigGenerator.cpp
 *
 *  Created on: 23.09.2014
 *      Author: chris
 */

#include "ConfigGenerator.h"

namespace HDDTest {

/**
 * All sizes in KB
 * size_start: Start of the block where data is written on to.
 * size_spread: Size of the block where data can be written to (last block: size_start + size_spread)
 * size_relation: Size of the relation, which is spread in extends.
 * size_extends: Size of one extend.
 * readMode: If every extend should be read from left to right or randomly.
 * extendDistribution: Wheter distanced between the extends are distrbuted equally over the available space or randomly.
 */
ConfigGenerator::ConfigGenerator(unsigned long long int size_start, unsigned long long int size_spread, unsigned long long int size_relation, unsigned long long int size_extends, enum mode_readMode readMode, enum mode_extendDistribution extendDistribution)
{
	this->size_start = size_start;
	this->size_spread = size_spread;
	this->size_relation = size_relation;
	this->size_extends = size_extends;
	this->readMode = readMode;
	this->extendDistribution = extendDistribution;
}

void ConfigGenerator::generate() {
	unsigned long long int noExtends = size_relation / size_extends; // number of extends we have

	if(readMode == LEFT_TO_RIGHT && extendDistribution == ED_CONSTANT) {
		// reading order of extends from left to right, equal distances between extends
		unsigned long long int sizeBetweenExtends = (size_spread - size_relation) / noExtends;

		// TODO DEBUG printf("number of extends: %llu\n", noExtends);
		// TODO DEBUG printf("size between extends: %llu\n", sizeBetweenExtends);
		for(unsigned long long int i = 0; i < noExtends; i++) {
			//struct startSize* tmp = new struct startSize;
			struct startSize tmp;
			tmp.start = size_start + i*size_extends + i*sizeBetweenExtends;
			tmp.size = size_extends;

			printf("iter %5llu: %10llu - %5llu\n", i, tmp.start, tmp.size);

			readOrder.push_back(tmp);
			//readOrder.push_back(*tmp);
		}
	}

	if(readMode == LEFT_TO_RIGHT && extendDistribution == ED_RANDOM) {
		// reading order of extends from left to right, random distances between extends
	}


	if(readMode == RM_RANDOM && extendDistribution == ED_CONSTANT) {
		// reading order of extends randomly, equal distances between extends
	}


	if(readMode == RM_RANDOM && extendDistribution == ED_RANDOM) {
		// reading order of extends randomly, random distances between extends

	}
}

    ConfigGenerator::~ConfigGenerator() {
	// TODO Auto-generated destructor stub
}

} /* namespace HDDTest */
