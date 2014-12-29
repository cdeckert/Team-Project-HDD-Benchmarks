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
#include "HDDModePageReader.h"

using namespace std;

int main(int argc, char** argv) {

    unsigned int iterations = 100000;
    unsigned int sectorSize = 512;
    unsigned int bufferSize = 1024;
    unsigned int stepSize_seeker = 1024*1014;

    vector<string> devices;
    string newDevice = "/dev/sdd";

    for(int i = 1; true; i++) {
    	std::cout << "enter address of device #"<<i<<" (type \"-\" for last one): " << std::flush;
		std::cin >> newDevice;
    	if(newDevice.compare("-") != 0) {
    		devices.push_back(newDevice);
    	} else {
    		break;
    	}
	}

    for(vector<string>::iterator curDevice = devices.begin(); curDevice != devices.end(); ++curDevice) {
		std::cout << "Test started for " << *curDevice << ": ";

		HDDTest::HDDModePageReader HDDModePageReader1 = HDDTest::HDDModePageReader(*curDevice);
		HDDModePageReader1.read();
		std::cout << HDDModePageReader1.getVendor() << " " << HDDModePageReader1.getDeviceName() << "\n";

		Benchmark::Skippy skippy = Benchmark::Skippy(*curDevice);
		skippy.configure(iterations, sectorSize, bufferSize);
		skippy.execute();

		Benchmark::Zoned zoned = Benchmark::Zoned(*curDevice);
		zoned.configure(bufferSize, 1024, 1024*1000);
		zoned.execute();

		Benchmark::Seeker seeker_mid = Benchmark::Seeker(*curDevice);
		seeker_mid.configure(sectorSize, stepSize_seeker, Benchmark::MIDDLE);
		seeker_mid.execute();

		Benchmark::Seeker seeker_begin = Benchmark::Seeker(*curDevice);
		seeker_begin.configure(sectorSize, stepSize_seeker, Benchmark::BEGINNING);
		seeker_begin.execute();
    }

    return 0;
}
