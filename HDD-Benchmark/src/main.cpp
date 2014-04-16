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
#include "HDDPropertyReader.h"

using namespace std;

int main(int argc, char** argv) {

	std:string device = "/dev/sda";
	HDDTest::HDDPropertyReader reader = HDDTest::HDDPropertyReader(device);
	reader.execute();

    return 0;
}

