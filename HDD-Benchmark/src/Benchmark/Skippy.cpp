#include "Skippy.h"
#include "Stopwatch.h"

#include <stdio.h>
#include <iostream>
#include <cmath>

namespace Benchmark
{

Skippy::Skippy(std::string theAddress): Benchmark(theAddress)
{
	this->fd = open64(theAddress.data(), O_RDWR | O_SYNC); //, O_DIRECT, O_LARGEFILE);
	perror("open");
	printf("FD %d",fd);
	perror("abc");
    lseek64(fd, 0L, SEEK_SET);
    perror("seek to start");
}

void Skippy::configure(int iterations, int singleSector, int bufferSize)
{
	this->iterations = iterations;
	this->singleSector = singleSector;
	perror("single");
	char* b = new char[bufferSize];
	this->buffer = b;
	perror("buffer");
}



inline void Skippy::runIteration(int iteration)
{
    lseek64(fd, (singleSector * iteration), SEEK_CUR);
    write(fd, &buffer,  sizeof(buffer));
}

void Skippy::execute()
{
	std::cout << "################" << std::endl << "#### SKIPPY ####" << std::endl << "################" << std::endl;
    Stopwatch stopwatch = Stopwatch(this->iterations);

    stopwatch.start();
    for(int i=0; i<iterations; i++)
    {

        printf("\rSkippy Test Status: %2.2f %%                      \r", round(i/(iterations/100)));

        this->runIteration(i);
        stopwatch.lap();
    }
    stopwatch.stop();
    HDDTest::ResultSaver resultSaver(this->device, "zoned", iterations);
	resultSaver.save(stopwatch);
}



Skippy::~Skippy() {
}

}

