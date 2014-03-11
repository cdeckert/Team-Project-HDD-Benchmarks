/* 
 * File:   main.cpp
 * Author: christiandeckert
 *
 * Created on March 8, 2014, 8:32 PM
 */


#include <cstdlib>
#include "Skippy.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    int iterations = 1000;
    
    Benchmark::Skippy skippy = Benchmark::Skippy("/dev/sdb");
    skippy.configure(iterations);
    
    return 0;
}

