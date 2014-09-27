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

		for(unsigned long long int i = 0; i < noExtends; i++) {
			struct startSize tmp;
			tmp.start = size_start + i*size_extends + i*sizeBetweenExtends;
			tmp.size = size_extends;

			// TODO DEBUG printf("iter %5llu: %10llu - %5llu\n", i, tmp.start, tmp.size);

			readOrder.push_back(tmp);
			//readOrder.push_back(*tmp);
		}
	}

	if(readMode == LEFT_TO_RIGHT && extendDistribution == ED_RANDOM) {
		// reading order of extends from left to right, random distances between extends
		unsigned long long int availableSlots = (size_spread - size_relation) / size_extends; // determins the number of maximum available extents in the range

		bool* slots = (bool*) calloc(availableSlots, sizeof(bool)); // let us know which slots is already used)
		printf("availableSlots: %llu\n", availableSlots); // TODO DEBUG
		unsigned long long int i = 0;
		init_rand();
		while(i < noExtends) { // find out which slots to use
			unsigned long long int newUsedSlot = rand() % availableSlots;

			if(slots[newUsedSlot] == true) // this slot is already used, try again
				continue;

			slots[newUsedSlot] = true;
			i++;
		}

		// generate config
		i = 0;
		for(unsigned long long int j = 0; j < availableSlots; j++) {
			if(slots[j]) {
				struct startSize tmp;
				tmp.start = size_start + j*size_extends;
				tmp.size = size_extends;

				//printf("iter %5llu: %10llu - %5llu\n", i, tmp.start, tmp.size);
				readOrder.push_back(tmp);
				i++;
			}
		}

		free(slots);
	}


	if(readMode == RM_RANDOM && extendDistribution == ED_CONSTANT) {
		// reading order of extends randomly, equal distances between extends  --------------------------------------------------
		unsigned long long int sizeBetweenExtends = (size_spread - size_relation) / noExtends;

		bool* slots = (bool*) calloc(noExtends, sizeof(bool)); // let us know which slots is already used)
		unsigned long long int i = 0;
		init_rand();
		while(i < noExtends) { // find out which slots to use
			unsigned long long int newUsedSlot = rand() % noExtends;

			if(slots[newUsedSlot] == true) // this slot is already used, try again
				continue;

			// generate config
			struct startSize tmp;
			tmp.start = size_start + newUsedSlot*size_extends + newUsedSlot*sizeBetweenExtends;
			//tmp.start = size_start + newUsedSlot*size_extends;
			tmp.size = size_extends;

			//printf("iter %5llu: %10llu - %5llu\n", i, tmp.start, tmp.size);
			readOrder.push_back(tmp);
			slots[newUsedSlot] = true;
			i++;
		}
		free(slots);
	}


	if(readMode == RM_RANDOM && extendDistribution == ED_RANDOM) {
		// reading order of extends randomly, random distances between extends
		unsigned long long int availableSlots = (size_spread - size_relation) / size_extends; // determins the number of maximum available extents in the range

		bool* slots = (bool*) calloc(availableSlots, sizeof(bool)); // let us know which slots is already used)
		// TODO DEBUG printf("availableSlots: %llu\n", availableSlots);
		unsigned long long int i = 0;
		init_rand();
		while(i < noExtends) { // find out which slots to use
			unsigned long long int newUsedSlot = rand() % availableSlots;

			if(slots[newUsedSlot] == true) // this slot is already used, try again
				continue;

			// generate config
			struct startSize tmp;
			tmp.start = size_start + newUsedSlot*size_extends;
			tmp.size = size_extends;

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
        return readOrder;}

    unsigned long long int ConfigGenerator::getSizeExtends() const
    {
        return size_extends;
    }

    unsigned long long int ConfigGenerator::getSizeStart() const
    {
        return size_start;
    }

    void ConfigGenerator::setSizeStart(unsigned long long int sizeStart)
    {
        size_start = sizeStart;}

    ConfigGenerator::~ConfigGenerator() {
	// TODO Auto-generated destructor stub
}

    std::string ConfigGenerator::configToString() {

    	std::string result = "";
    	result += "used block start: @" + std::to_string((this->size_start)/1024);
    	result += "MB (size: " + std::to_string((this->size_spread)/1024) + "MB)\n";
    	result += "size of relation: " + std::to_string(size_relation/1024)+"MB\n";
    	result += "size of one extent: " + std::to_string(size_extends)+"KB\n";
    	result += "read mode: ";
    	result += ((readMode == 0) ? "left to right" : "random");
    	result += "\n";
    	result += "extent distribution: ";
    	result += ((extendDistribution == 0) ? "static" : "random");
    	result += "\n";
    	return result;
    }
    void ConfigGenerator::init_rand() {
    	time_t t;

		time(&t);
		srand((unsigned int)t);              /* Zufallsgenerator initialisieren */
    }


} /* namespace HDDTest */
