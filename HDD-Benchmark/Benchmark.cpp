/* 
 * File:   Benchmark.cpp
 * Author: christiandeckert
 * 
 * Created on March 8, 2014, 8:33 PM
 */

#include "Benchmark.h"




Benchmark::Benchmark(char *theAddress) {
    SINGLE_SECTOR = 512;
    fd = open64(theAddress, O_RDWR|O_DIRECT|O_LARGEFILE);
    perror("open");
}

int Benchmark::getFd()
{
    return fd;
}

Benchmark::~Benchmark() {
}

