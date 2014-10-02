/*
* File: main.cpp
* Author: chris
*
* Created on September 23, 2014, 01:06 PM
*/

#include <iostream>
#include "ConfigGenerator.h"
#include "ExecuteTest.h"

using namespace std;

int main(int argc, char **argv)
{
	unsigned long long int size_start = 0;
	unsigned long long int size_spread = 1024 * 1024 * 3;
	unsigned long long int size_relation = 1024 * 1024;
	unsigned long long int size_extends = 64;
	enum HDDTest::mode_readMode readMode = HDDTest::RM_RANDOM;
	enum HDDTest::mode_extendDistribution extendDistribution = HDDTest::ED_CONSTANT;

	std::string device = "/dev/sdb";
	std::cout << "Enter device address: " << std::flush;
	std::cin >> device;

	HDDTest::ConfigGenerator confGen = HDDTest::ConfigGenerator(size_start, size_spread, size_relation, size_extends, readMode, extendDistribution);
	confGen.generate();

	HDDTest::ExecuteTest exec = HDDTest::ExecuteTest(device);
	double time = exec.execute(&confGen);
	cout << "Time: " << time << "s\n";
	return 0;
}
