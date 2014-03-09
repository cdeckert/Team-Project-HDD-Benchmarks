/* 
 * File:   main.cpp
 * Author: christiandeckert
 *
 * Created on March 8, 2014, 8:32 PM
 */


#include <cstdlib>
#include "Stopwatch.h"
#include "Skippy.h"
#include <cmath>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Stopwatch stopwatch = Stopwatch();
    
    Skippy skippy = Skippy("/dev/sdb");
    
    stopwatch.start();
    int iterations = 50000;
    for(int i=0; i<iterations; i++)
    {
        std::cout << "\b\b\b\b\b\b" << round(i*100/iterations)/100 << "%";
        skippy.execute(i);
        stopwatch.lap();
    }
    stopwatch.stop();
    
    return 0;
}

