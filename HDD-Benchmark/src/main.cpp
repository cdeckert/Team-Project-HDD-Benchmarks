/* 
 * File:   main.cpp
 * Author: christiandeckert
 *
 * Created on March 8, 2014, 8:32 PM
 */


#include <cstdlib>
#include "Skippy.h"
#include "Zoned.h"
#include "Seeker.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    int iterations = 1000;
    int sectorSize = 512;
    int bufferSize = 1024;
    std::string device = "/dev/sdb";

    /*Benchmark::Skippy skippy = Benchmark::Skippy(device);
	skippy.configure(iterations, sectorSize, bufferSize);
	skippy.execute();*/

    /*Benchmark::Zoned zoned = Benchmark::Zoned(device);
    zoned.configure(bufferSize, 1024, 1024*1000);
    zoned.execute();*/

    Benchmark::Seeker seeker = Benchmark::Seeker(device);
    seeker.configure(sectorSize, sectorSize);

    try {
        seeker.execute();
    } catch(std::bad_alloc& ba) {
    	std::cerr << "bad alloc: " << ba.what() << "\n";
    }


    return 0;
}

