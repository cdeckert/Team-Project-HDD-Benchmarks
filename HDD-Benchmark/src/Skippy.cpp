#include "Skippy.h"
#include "Stopwatch.h"

#include <stdio.h>
#include <iostream>
#include <cmath>

namespace Benchmark
{

Skippy::Skippy(std::string theAddress): Benchmark(theAddress)
{
	this->device = theAddress;
	this->testName = "skippy";
	this->fd = open64(theAddress.data(), O_DIRECT); //O_RDWR | O_SYNC);

	blockSize = 0;
	int rc = ioctl(fd, BLKSSZGET, &blockSize);
	if(fd == -1)
		perror("IOCTL BLKSSZGET");

    lseek64(fd, 0L, SEEK_SET);
}

void Skippy::configure(int iterations, int singleSector, int bufferSize)
{
	this->iterations = iterations;
	this->singleSector = singleSector;
	//perror("single");
	this->buffer = (char*)memalign(blockSize,calcBufferSize(bufferSize));
	if (buffer == NULL) {
		perror("ERROR MEMALIGN");
	}
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
    HDDTest::ResultSaver resultSaver(this);
	resultSaver.save(stopwatch);
}

std::string Skippy::getResultName() {
	return testName +"-"+std::to_string(iterations);
}



Skippy::~Skippy() {
}

}

