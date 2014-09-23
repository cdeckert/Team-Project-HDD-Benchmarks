/*
* File: main.cpp
* Author: chris
*
* Created on September 23, 2014, 01:06 PM
*/

#include <iostream>
#include "ConfigGenerator.h"

using namespace std;

int main(int argc, char** argv) {
	unsigned long long int size_start = 0;
	unsigned long long int size_spread = 1024*1024*3;
	unsigned long long int size_relation = 1024*1024;
	unsigned long long int size_extends = 64;
	enum HDDTest::mode_readMode readMode = HDDTest::LEFT_TO_RIGHT;
	enum HDDTest::mode_extendDistribution extendDistribution = HDDTest::ED_CONSTANT;

	HDDTest::ConfigGenerator confGen = HDDTest::ConfigGenerator(size_start, size_spread, size_relation, size_extends, readMode, extendDistribution);
	confGen.generate();

    return 0;
}
