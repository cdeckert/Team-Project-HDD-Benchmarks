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

void Benchmark::Seeker::configure(unsigned int sectorSize, unsigned int stepSize) {
	this->sectorSize = sectorSize;
	this->stepSize = stepSize;
	this->buffer = new char[sectorSize];

	this->iterations = diskSize;
	this->iterations /= stepSize;
}

void Benchmark::Seeker::execute() {
	std::cout << "################" << std::endl << "#### SEEKER ####" << std::endl << "################" << std::endl;
	std::cout << "iterations: " << iterations << std::endl;


	Stopwatch stopwatch = Stopwatch(iterations);

	for(long long int i = 0; i < iterations; i++) {
		printf("\rSkippy Test Status: %2.2f %%             \r", i*1.0/(iterations/100));
		// jump back to start
		lseek64(fd, 0, SEEK_SET);
		write(fd, &buffer, sectorSize);

		// time from HERE!
		stopwatch.start();
		lseek64(fd, i * stepSize, SEEK_SET);
		write(fd, &buffer, sectorSize);
		stopwatch.lap();
		// to HERE!
	}

	stopwatch.stop();
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
