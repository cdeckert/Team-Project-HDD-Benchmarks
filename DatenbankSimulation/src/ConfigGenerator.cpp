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
 * size_spread: Size of the block where data can be written to (last block: size_start + size_spread)
 * size_relation: Size of the relation, which is spread in extents.
 * size_extents: Size of one extent.
 * readMode: If every extent should be read from left to right or randomly.
 * extentDistribution: Wheter distanced between the extents are distrbuted equally over the available space or randomly.
 */
ConfigGenerator::ConfigGenerator(unsigned long long int size_start, unsigned long long int size_spread,
								 unsigned long long int size_relation, unsigned long long int size_extents,
								 enum mode_readMode readMode, enum mode_extentDistribution extentDistribution)
{
	this->size_start = size_start;
	this->size_spread = size_spread;
	this->size_relation = size_relation;
	this->size_extents = size_extents;
	this->readMode = readMode;
	this->extentDistribution = extentDistribution;
}

/**
* ggenerates for different cases along the 2 dimentions readMode and extentDistribution
*/
void ConfigGenerator::generate()
{
	unsigned long long int noextents = size_relation / size_extents; // number of extents we have

	if (readMode == LEFT_TO_RIGHT && extentDistribution == ED_CONSTANT)
	{
		// reading order of extents from left to right, equal distances between extents
		unsigned long long int sizeBetweenextents = (size_spread - size_relation) / noextents;

		for (unsigned long long int i = 0; i < noextents; i++)
		{
			struct startSize tmp;
			tmp.start = size_start + i * size_extents + i * sizeBetweenextents;
			tmp.size = size_extents;

			// TODO DEBUG printf("iter %5llu: %10llu - %5llu\n", i, tmp.start, tmp.size);

			readOrder.push_back(tmp);
			//readOrder.push_back(*tmp);
		}
	}

	else if (readMode == LEFT_TO_RIGHT && extentDistribution == ED_RANDOM)
	{
		// reading order of extents from left to right, random distances between extents
		unsigned long long int availableSlots = (size_spread - size_relation) / size_extents; // determins the number of maximum available extents in the range

		bool *slots = (bool *) calloc(availableSlots, sizeof(bool)); // let us know which slots is already used)
		printf("availableSlots: %llu\n", availableSlots); // TODO DEBUG
		unsigned long long int i = 0;
		init_rand();
		while (i < noextents)  // find out which slots to use
		{
			unsigned long long int newUsedSlot = rand() % availableSlots;

			if (slots[newUsedSlot] == true) // this slot is already used, try again
			{
				continue;
			}
			slots[newUsedSlot] = true;
			i++;
		}

		// generate config
		i = 0;
		for (unsigned long long int j = 0; j < availableSlots; j++)
		{
			if (slots[j])
			{
				struct startSize tmp;
				tmp.start = size_start + j * size_extents;
				tmp.size = size_extents;

				//printf("iter %5llu: %10llu - %5llu\n", i, tmp.start, tmp.size);
				readOrder.push_back(tmp);
				i++;
			}
		}

		free(slots);
	}


	else if (readMode == RM_RANDOM && extentDistribution == ED_CONSTANT)
	{
		// reading order of extents randomly, equal distances between extents  --------------------------------------------------
		unsigned long long int sizeBetweenextents = (size_spread - size_relation) / noextents;

		bool *slots = (bool *) calloc(noextents, sizeof(bool)); // let us know which slots is already used)
		unsigned long long int i = 0;
		init_rand();
		while (i < noextents)  // find out which slots to use
		{
			unsigned long long int newUsedSlot = rand() % noextents;

			if (slots[newUsedSlot] == true) // this slot is already used, try again
			{
				continue;
			}

			// generate config
			struct startSize tmp;
			tmp.start = size_start + newUsedSlot * size_extents + newUsedSlot * sizeBetweenextents;
			//tmp.start = size_start + newUsedSlot*size_extents;
			tmp.size = size_extents;

			//printf("iter %5llu: %10llu - %5llu\n", i, tmp.start, tmp.size);
			readOrder.push_back(tmp);
			slots[newUsedSlot] = true;
			i++;
		}
		free(slots);
	}


	else if (readMode == RM_RANDOM && extentDistribution == ED_RANDOM)
	{
		// reading order of extents randomly, random distances between extents
		unsigned long long int availableSlots = (size_spread - size_relation) / size_extents; // determins the number of maximum available extents in the range

		bool *slots = (bool *) calloc(availableSlots, sizeof(bool)); // let us know which slots is already used)
		// TODO DEBUG printf("availableSlots: %llu\n", availableSlots);
		unsigned long long int i = 0;
		init_rand();
		while (i < noextents)  // find out which slots to use
		{
			unsigned long long int newUsedSlot = rand() % availableSlots;

			if (slots[newUsedSlot] == true) // this slot is already used, try again
				continue;

			// generate config
			struct startSize tmp;
			tmp.start = size_start + newUsedSlot * size_extents;
			tmp.size = size_extents;

			//printf("iter %5llu: %10llu - %5llu\n", i, tmp.start, tmp.size);
			readOrder.push_back(tmp);
			slots[newUsedSlot] = true;
			i++;
		}
		free(slots);
	}
}

std::vector<struct startSize> ConfigGenerator::getReadOrder() const
{
	return readOrder;
}

unsigned long long int ConfigGenerator::getSizeExtents() const
{
	return size_extents;
}

unsigned long long int ConfigGenerator::getSizeStart() const
{
	return size_start;
}

void ConfigGenerator::setSizeStart(unsigned long long int sizeStart)
{
	size_start = sizeStart;
}

ConfigGenerator::~ConfigGenerator()
{
	// TODO Auto-generated destructor stub
}

std::string ConfigGenerator::configToString()
{

	std::string result = "";
	result += "used block start: @" + std::to_string((this->size_start) / 1024);
	result += "MB (size: " + std::to_string((this->size_spread) / 1024) + "MB)\n";
	result += "size of relation: " + std::to_string(size_relation / 1024) + "MB\n";
	result += "size of one extent: " + std::to_string(size_extents) + "KB\n";
	result += "read mode: ";
	result += ((readMode == 0) ? "left to right" : "random");
	result += "\n";
	result += "extent distribution: ";
	result += ((extentDistribution == 0) ? "static" : "random");
	result += "\n";
	return result;
}


void ConfigGenerator::init_rand()
{
	time_t t;

	time(&t);
	srand((unsigned int)t);              /* Zufallsgenerator initialisieren */
}


} /* namespace HDDTest */
