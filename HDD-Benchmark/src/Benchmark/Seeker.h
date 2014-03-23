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

namespace Benchmark {

class Seeker: public Benchmark::Benchmark {
public:
	Seeker(std::string);
	void execute();
	void configure(int, int);
	~Seeker();
private:
	int fd;
	off64_t diskSize;
	int largeSize;
	int measurements;
	int singleSector;
	char* buffer;
	void measureSize();
};

} /* namespace HDDTest */
#endif /* SEEKER_H_ */
