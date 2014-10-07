/*
* File: main.cpp
* Author: chris
*
* Created on September 23, 2014, 01:06 PM
*/

#include <iostream>
#include "ConfigGenerator.h"
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
	/**
	 * CALL: DatenbankSimulation [DEVICE readMode extentDistribution noOfRelations]
	 * Caution: Relation weights cannot yet be inputted over command line.
	 */

	// hdd starts at 0
	unsigned long long int size_start = 0;
	// spreading of relationship table
	unsigned long long int size_spread = 1024 * 1024 * 3;
	// size of a single extent
	unsigned long long int size_extent = 64;
	// size of a single page
	unsigned long long int size_page = 8;

	enum HDDTest::mode_readMode readMode;
	enum HDDTest::mode_extentDistribution extentDistribution;

	std::string device = "/dev/sdb";
	// define read mode: ORDERED or UNORDERED
	readMode = HDDTest::ORDERED;
	// distribution: EQUALLY or ED_RANDOM
	extentDistribution = HDDTest::EQUALLY;
	char no_of_relations = 3;
	char relation_distribution[] = {4,1,3,1,1,1,1,1}; // standard distribution of the relations


	if(argc <= 4) {
		std::cout << "Enter device address: " << std::flush;
		std::cin >> device;
	} else {
		device = std::string(argv[1]);
		readMode = (atoi(argv[2]) == 0) ? HDDTest::ORDERED : HDDTest::UNORDERED;
		extentDistribution = (atoi(argv[3]) == 0) ? HDDTest::EQUALLY : HDDTest::ED_RANDOM;
		no_of_relations = atoi(argv[4]);
	}

	HDDTest::ConfigGenerator confGen = HDDTest::ConfigGenerator(
										   size_start, size_spread,
										   size_extent, size_page, readMode,
										   extentDistribution, no_of_relations, relation_distribution);
	// generate configuration
	confGen.generate();

	return 0;
}
