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
#include <algorithm>

namespace HDDTest
{

enum mode_readMode {ORDERED, UNORDERED};
enum mode_extentDistribution {EQUALLY , ED_RANDOM};

struct extent
{
	char relation_no; // number of relation
	unsigned long long int start; // in KB
};

class ConfigGenerator
{
private:
	// start of relations
	unsigned long long int size_start;
	// spreading of a single relation
	unsigned long long int size_spread;
	// extent size
	unsigned long long int size_extent;
	// page size
	unsigned long long int size_page;
	enum mode_readMode readMode;
	enum mode_extentDistribution extentDistribution;
	//
	char no_of_relations;
	char* relation_distribution;

	// marks start and size of what is read (in kb)
	std::vector<struct extent> extentList;

	// like extentList but for each relation separate. extentListOfRel[i] stores all extents of relation i
	std::vector<struct extent>* extentListOfRel;

	void init_rand();

public:
	ConfigGenerator(unsigned long long int size_start, unsigned long long int size_spread,
					unsigned long long int size_extents, unsigned long long int size_page,
					enum mode_readMode readMode, enum mode_extentDistribution extentDistribution,
					char no_of_relations, char* relation_distribution);
	~ConfigGenerator();

	void generate();
	std::vector<struct extent> getAllExtentAllocations() const;
	unsigned long long int getSizeExtents() const;
	unsigned long long int getSizeStart() const;
	void setSizeStart(unsigned long long int sizeStart);
	std::vector<struct extent>* getExtentLocationsOfRel(char);
	unsigned long long int getOneExtentOfRel(char);
	unsigned long long int getOnePageOfRel(char);
	std::string configToString();
    char getNoOfRelations() const;
};

} /* namespace HDDTest */
#endif /* CONFIGGENERATOR_H_ */
