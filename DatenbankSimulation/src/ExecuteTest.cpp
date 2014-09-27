/*
 * ExecuteTest.cpp
 *
 *  Created on: 27.09.2014
 *      Author: chris
 */

#include "ExecuteTest.h"
#include <iostream>

namespace HDDTest {

ExecuteTest::ExecuteTest(std::string device) {
	this->device = device;
}

double ExecuteTest::execute(ConfigGenerator* config) {
	std::cout << "#################" << std::endl << "# DB SIMULATION #" << std::endl << "#################" << std::endl;
	std::cout << config->configToString() << "\n";

	// reserve space for reading
	char* buffer = (char*) malloc(config->getSizeExtends()*1024);

	// open device
	this->fd = open64(device.data(), O_RDWR | O_SYNC);

	//read a byte to make sure it is spined up
	read(fd, buffer, 1);
	lseek64(fd, 0, SEEK_SET);

	std::vector<struct startSize> readOrder = config->getReadOrder();

	// initialize stop watch
	Stopwatch stopwatch = Stopwatch(1);
	stopwatch.start();

	for(size_t i = 0; i < readOrder.size(); i++) {
		struct startSize cur = readOrder.at(i);

		lseek64(fd, (cur.start*1024), SEEK_SET);
		read(fd, buffer, (cur.size*1024));

		printf("\rstatus: iteration %7llu,  %2.2f %%                      \r", (unsigned long long int)i, (double)i/(readOrder.size()/100));
	}
	printf("\n");

	stopwatch.lap();
	stopwatch.stop();
	return stopwatch.getTotalTime();
}

ExecuteTest::~ExecuteTest() {
	// TODO Auto-generated destructor stub
}

} /* namespace HDDTest */
