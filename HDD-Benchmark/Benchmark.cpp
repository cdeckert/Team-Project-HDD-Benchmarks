/* 
 * File:   Benchmark.cpp
 * Author: christiandeckert
 * 
 * Created on March 8, 2014, 8:33 PM
 */

#include "Benchmark.h"

namespace Benchmark {


Benchmark::Benchmark(char *theAddress) {
    SINGLE_SECTOR = 512;
    fd = open64(theAddress, O_RDWR | O_SYNC); //, O_DIRECT, O_LARGEFILE);
    perror("open");
}

int Benchmark::getFd()
{
    return fd;
}

int Benchmark::getSingleSector()
{
    return SINGLE_SECTOR;
}

Benchmark::~Benchmark() {
}

}
