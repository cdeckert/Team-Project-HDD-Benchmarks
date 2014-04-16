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
	this->testName = "seeker";
	this->fd = open64(theAddress.data(), O_RDWR | O_SYNC);
	perror("open");
	measureSize();

}

Seeker::~Seeker() {
	delete[] buffer;
}

}

void Benchmark::Seeker::configure(unsigned int sectorSize, unsigned int stepSize, enum seeker_return_mode returnMode) {
	this->sectorSize = sectorSize;
	this->stepSize = stepSize;
	this->returnMode = returnMode;
	this->buffer = new char[sectorSize];

	this->iterations = diskSize;
	this->iterations /= stepSize;
}

void Benchmark::Seeker::execute() {
	std::cout << "################" << std::endl << "#### SEEKER ####" << std::endl << "################" << std::endl;
	std::cout << "iterations: " << iterations << std::endl;

	// initialize stopwatch
	Stopwatch stopwatch = Stopwatch(iterations);

	// Seeker itself
	for(long long int i = 0; i < iterations; i++) {
		printf("\rSeeker Test Status: %2.2f %%             \r", i*1.0/(iterations/100));
		// jump back
		switch(returnMode) {
			case MIDDLE:
				lseek64(fd, diskSize/2, SEEK_SET);
				break;
			default:
				// BEGINNING
				lseek64(fd, 0, SEEK_SET);
				break;
		}
		write(fd, &buffer, sectorSize);

		// time from HERE!
		stopwatch.start();
		lseek64(fd, i * stepSize, SEEK_SET);
		write(fd, &buffer, sectorSize);
		stopwatch.lap();
		// to HERE!
	}

	stopwatch.stop();
	//TODO ENTFERNEN
    //HDDTest::ResultSaver resultSaver(this->device, "seeker");
    HDDTest::ResultSaver resultSaver(this);

	resultSaver.save(stopwatch);
}

std::string Benchmark::Seeker::getResultName() {
	std::string res = testName +"-"+std::to_string(stepSize)+"-";
	switch(returnMode) {
		case MIDDLE:
			res += "middle";
			break;
		default:
			// BEGINNING
			res += "beginning";
			break;
	}
	return res;
}

void Benchmark::Seeker::measureSize() {
	lseek64(fd, 0L, SEEK_SET);
	this->diskSize = lseek64(fd, 0L, SEEK_END);
	std::cout << diskSize << "DISK\n";
	lseek64(fd, 0L, SEEK_SET);
}

 /* namespace HDDTest */
