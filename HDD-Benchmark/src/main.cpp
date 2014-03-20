/* 
 * File:   main.cpp
 * Author: christiandeckert
 *
 * Created on March 8, 2014, 8:32 PM
 */


#include <cstdlib>
#include "Skippy.h"
#include "Zoned.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    int iterations = 1000;
    int sectorSize = 512;
    int bufferSize = 1024;
    std::string device = "/dev/sdb";
    /*Benchmark::Zoned zoned = Benchmark::Zoned(device);
    zoned.configure(bufferSize, 1024, 1024*1000);
    zoned.execute();*/

    Benchmark::Skippy skippy = Benchmark::Skippy(device);
    skippy.configure(iterations, sectorSize, bufferSize);
    skippy.execute();
    return 0;
}

