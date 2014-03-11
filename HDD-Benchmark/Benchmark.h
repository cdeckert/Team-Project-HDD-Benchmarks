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
/*
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>
#include <stdio.h>
#include <ctime>*/

namespace Benchmark {

class Benchmark {
public:
    Benchmark(char*);
    virtual void execute(int) = 0;
    
    int getFd();
    int getSingleSector();
    virtual ~Benchmark();
private:
    int fd;
    int SINGLE_SECTOR;
};

}

#endif	/* BENCHMARK_H */

