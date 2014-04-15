/*
 * Seeker.h
 *
 *  Created on: 23.03.2014
 *      Author: chris
 */

#ifndef SEEKER_H_
#define SEEKER_H_

#include "Benchmark.h"
#include "ResultSaver.h"
#include <cmath>

namespace Benchmark {

class Seeker: public Benchmark::Benchmark {
public:
	Seeker(std::string);
	void execute();
	void configure(unsigned int, unsigned int);
    std::string getResultName();
	~Seeker();
private:
	int fd;
	off64_t diskSize;
	unsigned int sectorSize;
	unsigned int stepSize;
	unsigned int iterations;
	char* buffer;
	void measureSize();
};

} /* namespace HDDTest */
#endif /* SEEKER_H_ */
