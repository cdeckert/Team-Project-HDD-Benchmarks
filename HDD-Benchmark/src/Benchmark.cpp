/* 
 * File:   Benchmark.cpp
 * Author: christiandeckert
 * 
 * Created on March 8, 2014, 8:33 PM
 */

#include "Benchmark.h"

namespace Benchmark {

Benchmark::Benchmark(std::string device) {
}

void Benchmark::execute() {
}

std::string Benchmark::getResultName() {
}

std::string Benchmark::getDevice() {
	return this->device;
}

std::string Benchmark::getTestName() {
	return std::string(this->testName);
}


Benchmark::~Benchmark() {
}

size_t Benchmark::calcBufferSize(size_t minBufferSize) {
	size_t tmpSize = minBufferSize*1024/blockSize;
	if(minBufferSize*1024%blockSize != 0)
		tmpSize += blockSize;
	return tmpSize;
}

}

