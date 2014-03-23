/*
 * Seeker.cpp
 *
 *  Created on: 23.03.2014
 *      Author: chris
 */

#include "Seeker.h"

namespace Benchmark {

Seeker::Seeker(std::string theAddress): Benchmark(theAddress) {
	this->device = theAddress;
	this->fd = open64(theAddress.data(), O_RDWR | O_SYNC);
	perror("open");
	measureSize();

}

Seeker::~Seeker() {
	delete[] buffer;
}

}

void Benchmark::Seeker::configure(unsigned int singleSector, unsigned int largeSize) {
	this->measurements = singleSector / largeSize;
	this->singleSector = singleSector;
	this->largeSize = largeSize;
	this->buffer = new char[singleSector];

	this->iterations = diskSize;
	this->iterations /= largeSize;
	this->iterations *= measurements;
}

void Benchmark::Seeker::execute() {
	std::cout << "################" << std::endl << "#### SEEKER ####" << std::endl << "################" << std::endl;
	std::cout << "iterations: " << iterations << std::endl;


	Stopwatch stopwatch = Stopwatch(iterations);
    //stopwatch.start();

	for(long long int base = 0; base < diskSize; base += largeSize) {
		for(unsigned int i = 0; i < measurements; i++) {
			// jump back to start
			lseek64(fd, 0, SEEK_SET);
			write(fd, &buffer, singleSector);

			// time from HERE!
			//stopwatch.start();
			lseek64(fd, base + (i * singleSector), SEEK_SET);
			write(fd, &buffer, singleSector);
			//stopwatch.lap();
			// to HERE!
		}
	}

	//stopwatch.stop();
    HDDTest::ResultSaver resultSaver(this->device, "seeker");
	resultSaver.save(stopwatch);
}

void Benchmark::Seeker::measureSize() {
	lseek64(fd, 0L, SEEK_SET);
	this->diskSize = lseek64(fd, 0L, SEEK_END);
	std::cout << diskSize << "DISK\n";
	lseek64(fd, 0L, SEEK_SET);
}

 /* namespace HDDTest */
