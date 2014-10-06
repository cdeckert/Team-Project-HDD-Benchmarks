/*
* File: main.cpp
* Author: chris
*
* Created on September 23, 2014, 01:06 PM
*/

#include <iostream>
#include "ConfigGenerator.h"
#include "ExecuteTest.h"
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
	// hdd starts at 0
	unsigned long long int size_start = 0;
	// spreading of relationship table
	unsigned long long int size_spread = 1024 * 1024 * 3;
	// size of relationship table
	unsigned long long int size_relation = 1024 * 1024;
	// size of a single extent
	unsigned long long int size_extents = 64;

	enum HDDTest::mode_readMode readMode;
	enum HDDTest::mode_extentDistribution extentDistribution;

	std::string device = "/dev/sdb";

	if(argc <= 3) {
		// define read mode: LEFT_TO_RIGHT or RM_RANDOM
		readMode = HDDTest::RM_RANDOM;

		// distribution: ED_CONSTANT or ED_RANDOM
		extentDistribution = HDDTest::ED_CONSTANT;

		std::cout << "Enter device address: " << std::flush;
		std::cin >> device;
	} else {
		readMode = (atoi(argv[2]) == 0) ? HDDTest::LEFT_TO_RIGHT : HDDTest::RM_RANDOM;
		extentDistribution = (atoi(argv[3]) == 0) ? HDDTest::ED_CONSTANT : HDDTest::ED_RANDOM;
		device = std::string(argv[1]);
	}


	HDDTest::ConfigGenerator confGen = HDDTest::ConfigGenerator(
										   size_start, size_spread,
										   size_relation, size_extents,
										   readMode, extentDistribution);
	// generate configuration
	confGen.generate();

	// execute tests
	HDDTest::ExecuteTest exec = HDDTest::ExecuteTest(device);
	double time = exec.execute(&confGen);
	cout << "Time: " << time << "s\n";
	return 0;
}
