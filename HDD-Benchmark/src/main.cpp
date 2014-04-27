/*
* File: main.cpp
* Author: christiandeckert
*
* Created on March 8, 2014, 8:32 PM
*/


#include <cstdlib>
#include "Skippy.h"
#include "Zoned.h"
#include "Seeker.h"

using namespace std;

int main(int argc, char** argv) {

    unsigned int iterations = 1000;
    unsigned int sectorSize = 512;
    unsigned int bufferSize = 1024;
    unsigned int stepSize_seeker = 1024*1014;
    std::string device = "/dev/sdb";

    /*Benchmark::Skippy skippy = Benchmark::Skippy(device);
<<<<<<< HEAD
	skippy.configure(iterations, sectorSize, bufferSize);
	skippy.execute();

    Benchmark::Zoned zoned = Benchmark::Zoned(device);
    zoned.configure(bufferSize, 1024, 1024*1000);
    zoned.execute();*/
=======
skippy.configure(iterations, sectorSize, bufferSize);
skippy.execute();

Benchmark::Zoned zoned = Benchmark::Zoned(device);
zoned.configure(bufferSize, 1024, 1024*1000);
zoned.execute();*/
>>>>>>> origin/feature/PropertyReader

    Benchmark::Seeker seeker = Benchmark::Seeker(device);
    seeker.configure(sectorSize, stepSize_seeker, Benchmark::MIDDLE);
    seeker.execute();


    return 0;
}
