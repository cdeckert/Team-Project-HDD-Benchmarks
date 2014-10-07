/*
 * ConfigGenerator.cpp
 *
 *  Created on: 23.09.2014
 *      Author: chris
 */

#include "ConfigGenerator.h"

namespace HDDTest
{

/**
 * All sizes in KB
 * size_start: Start of the block where data is written on to.
 * size_spread: Size of the block where data can be written to (last block: size_start + size_spread) (use dummy relation to create spaces)
 * size_extent: Size of one extent.
 * size_page: Size of one page.
 * extentDistribution: Whether distanced between the extents are distrbuted equally over the available space or randomly.
 * no_of_relations: Total number of relations created.
 * relation_distribution: Array holding weights of the relations. E.g. 5,5,5 would create three equally sized relations.
 */
ConfigGenerator::ConfigGenerator(unsigned long long int size_start, unsigned long long int size_spread,
								 unsigned long long int size_extent, unsigned long long int size_page,
								 enum mode_readMode readMode, enum mode_extentDistribution extentDistribution,
								 char no_of_relations, char* relation_distribution)
{
	this->size_start = size_start;
	this->size_spread = size_spread;
	this->size_extent = size_extent;
	this->size_page = size_page;
	this->readMode = readMode;
	this->extentDistribution = extentDistribution;
	this->no_of_relations = no_of_relations;
	this->relation_distribution = relation_distribution;
}

/**
* generates different cases along the dimension extentDistribution
*/
void ConfigGenerator::generate()
{
	unsigned long long int noextents = size_spread / size_extent; // number of extents we have

	// sum of all weights of the relations
	unsigned short allRelationWeights = 0;
	for(int i = 0; i < no_of_relations; i++) {
		allRelationWeights += relation_distribution[i];
	}

	// needed later for calculating which relation the extent belongs to
	char relationsMod[allRelationWeights];
	int k = 0; // count var
	for(int i = 0; i < no_of_relations; i++) {
		for(int j = 0; j < relation_distribution[i]; j++) {
			relationsMod[k] = i;
			k++;
		}
	}

	// create separate lists for each relation
	extentListOfRel = (std::vector<struct extent>*) calloc(no_of_relations, sizeof(std::vector<struct extent>));
	for(char i = 0; i < no_of_relations; i++) {
		extentListOfRel[(int)i] = std::vector<struct extent>();
	}

	if (extentDistribution == EQUALLY)
	{
		for (unsigned long long int i = 0; i < noextents; i++)
		{
			struct extent tmp;
			tmp.relation_no = relationsMod[i % allRelationWeights];
			tmp.start = size_start + i * size_extent;

			// TODO DEBUG printf("iter %llu: relation %3u | start: %5llu\n", i, tmp.relation_no, tmp.start);

			extentList.push_back(tmp);
			extentListOfRel[(int)tmp.relation_no].push_back(tmp);
		}
	}

	else if (extentDistribution == ED_RANDOM)
	{
		init_rand();
		for (unsigned long long int i = 0; i < noextents; i++)
		{
			struct extent tmp;
			tmp.relation_no = relationsMod[rand() % allRelationWeights];
			tmp.start = size_start + i * size_extent;

			// TODO DEBUG printf("iter %llu: relation %3u | start: %5llu\n", i, tmp.relation_no, tmp.start);

			extentList.push_back(tmp);
			extentListOfRel[(int)tmp.relation_no].push_back(tmp);
		}
	}

	// if readMode is set to UNORDERED randomize the specific lists
	if(readMode == UNORDERED) {
		for(int i = 0; i < no_of_relations; i++) {
			std::random_shuffle (extentListOfRel[(int)i].begin(),extentListOfRel[(int)i].end() );
		}
	}
}

/**
 * Get a vector with all extent locations (including relation number and start block in KB)
 */
std::vector<struct extent> ConfigGenerator::getAllExtentAllocations() const
{
	return extentList;
}

/**
 * Get the size of one extent (in KB).
 */
unsigned long long int ConfigGenerator::getSizeExtents() const
{
	return size_extent;
}

/**
 * Get the start point on the drive (in KB).
 */
unsigned long long int ConfigGenerator::getSizeStart() const
{
	return size_start;
}

ConfigGenerator::~ConfigGenerator()
{
	// TODO Auto-generated destructor stub
}

/**
 * Generate useful output which gives information about the setup of the run.
 */
std::string ConfigGenerator::configToString()
{

	std::string result = "";
	result += "used block start: @" + std::to_string((this->size_start) / 1024);
	result += "MB (size: " + std::to_string((this->size_spread) / 1024) + "MB)\n";
	result += "size of one extent: " + std::to_string(size_extent) + "KB\n";
	result += "\n";
	result += "extent distribution: ";
	result += ((extentDistribution == 0) ? "static" : "random");
	result += "\nno of relations: " + std::to_string(no_of_relations) + " (";
	for(int i = 0; i < no_of_relations; i++)
		result += " "+ std::to_string(relation_distribution[i]) + ",";
	result += ")\n";
	return result;
}


void ConfigGenerator::init_rand()
{
	time_t t;

	time(&t);
	srand((unsigned int)t);              /* Zufallsgenerator initialisieren */
}

/**
 * Total number of relations.
 */
char ConfigGenerator::getNoOfRelations() const
{
    return no_of_relations;
}

/**
 * Get a list with all extents belonging to one relation (caution: if extentDistribution is ED_RANDOM this vector in unsorted)
 */
std::vector<struct extent>* HDDTest::ConfigGenerator::getExtentLocationsOfRel(char relationNo)
{
	if(relationNo >= no_of_relations)
		perror("ConfigGenerator.cpp - getExtentLocationsOfRel: relation number too big!");

	return &extentListOfRel[(int)relationNo];
}

/**
 * Returns one random extent (position in KB) out of a relation.
 */
unsigned long long int HDDTest::ConfigGenerator::getOneExtentOfRel(char relationNo)
{
	std::vector<struct extent>* extentOfRel = getExtentLocationsOfRel(relationNo);
	init_rand();
	unsigned long long int no = rand() % extentOfRel->size();
	//TODO DEBUG printf("relationNo %3u | start: %5llu\n", extentOfRel->at(no).relation_no, extentOfRel->at(no).start);
	return extentOfRel->at(no).start;
}

/**
 * Returns one random page (position in KB) out of a relation.
 */
unsigned long long int HDDTest::ConfigGenerator::getOnePageOfRel(char relationNo)
{
	std::vector<struct extent>* extentOfRel = getExtentLocationsOfRel(relationNo);
	init_rand();
	unsigned long long int no = rand() % extentOfRel->size();
	unsigned long long int noOfPage = rand() % size_extent / size_page;
	//TODO DEBUG printf("relationNo %3u | start: %5llu\n", extentOfRel->at(no).relation_no, extentOfRel->at(no).start);
	return extentOfRel->at(no).start + noOfPage*size_page;
}


}






 /* namespace HDDTest */
