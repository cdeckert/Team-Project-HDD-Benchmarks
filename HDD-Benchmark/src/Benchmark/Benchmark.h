/* 
 * File:   Benchmark.h
 * Author: christiandeckert
 *
 * Created on March 8, 2014, 8:33 PM
 */

#ifndef BENCHMARK_H
#define	BENCHMARK_H

//#define _FILE_OFFSET_BITS 64
//#define _LARGEFILE64_SOURCE

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <stdio.h>
#include <iostream>


namespace Benchmark {

class Benchmark {
protected:
	std::string device;
public:
    Benchmark(std::string);
    virtual void execute() = 0;
    virtual ~Benchmark();
private:
};

}

#endif	/* BENCHMARK_H */

