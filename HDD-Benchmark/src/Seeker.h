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

// where the return address is (where seeker jumps to before jumping to its new measuring point)
enum seeker_return_mode {BEGINNING, MIDDLE};

class Seeker: public Benchmark::Benchmark {
public:
	Seeker(std::string);
	void execute();
	void configure(unsigned int, unsigned int, enum seeker_return_mode);
    std::string getResultName();
	~Seeker();
private:
	int fd;
	off64_t diskSize;
	unsigned int sectorSize;
	unsigned int stepSize;
	unsigned int iterations;
	enum seeker_return_mode returnMode;
	char* buffer;
	void measureSize();
};

} /* namespace HDDTest */
#endif /* SEEKER_H_ */
