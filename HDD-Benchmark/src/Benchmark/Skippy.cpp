/* 
 * File:   Skippy.cpp
 * Author: christiandeckert
 * 
 * Created on March 8, 2014, 8:35 PM
 */

#include "Skippy.h"
#include "Stopwatch.h"

#include <stdio.h>
#include <iostream>
#include <cmath>

namespace Benchmark {

Skippy::Skippy(std::string theAddress): Benchmark(theAddress){
	SINGLE_SECTOR = 512;
	fd = open64(theAddress.data(), O_RDWR | O_SYNC); //, O_DIRECT, O_LARGEFILE);
	perror("open");

    lseek64(getFd(), 0, SEEK_SET);
}

void Skippy::configure(int iterations) {
	this->iterations = iterations;
}



inline void Skippy::runIteration(int iteration)
{
    lseek64(getFd(), (getSingleSector() * iteration), SEEK_CUR);
    write(getFd(), &buffer,  sizeof(buffer));
}

void Skippy::execute() {
    Stopwatch stopwatch = Stopwatch(this->iterations);

    stopwatch.start();
    for(int i=0; i<iterations; i++)
    {

        printf("\rTest Status: %2.2f %%                      \r", round(i/(iterations/100)));

        this->runIteration(i);
        stopwatch.lap();
    }
    stopwatch.stop();
}

inline int Skippy::getSingleSector()
{
    return SINGLE_SECTOR;
}

inline int Skippy::getFd()
{
    return fd;
}


Skippy::~Skippy() {
}

}

