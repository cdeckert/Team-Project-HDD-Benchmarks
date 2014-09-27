/*
 * ExecuteTest.h
 *
 *  Created on: 27.09.2014
 *      Author: chris
 */

#ifndef EXECUTETEST_H_
#define EXECUTETEST_H_

#include "ConfigGenerator.h"
#include "Stopwatch.h"
#include <fcntl.h>
#include "HDDModePageReader.h"

namespace HDDTest {

class ExecuteTest {
private:
	std::string device;
	int fd;
public:
	ExecuteTest(std::string);
	double execute(ConfigGenerator*);
	~ExecuteTest();
};

} /* namespace HDDTest */
#endif /* EXECUTETEST_H_ */
