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

}
