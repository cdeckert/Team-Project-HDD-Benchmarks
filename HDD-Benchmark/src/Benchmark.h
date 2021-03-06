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
#include <linux/hdreg.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <malloc.h>


namespace Benchmark {

class Benchmark {
protected:
	std::string device;
	std::string testName;
	unsigned long blockSize;
	size_t calcBufferSize(size_t);
public:
    Benchmark(std::string);
    virtual void execute() = 0;
    virtual std::string getResultName() = 0;
    std::string getDevice();
    std::string getTestName();
    virtual ~Benchmark();
private:
};

}

#endif	/* BENCHMARK_H */

