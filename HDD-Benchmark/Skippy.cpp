/* 
 * File:   Skippy.cpp
 * Author: christiandeckert
 * 
 * Created on March 8, 2014, 8:35 PM
 */

#include "Skippy.h"

#include <stdio.h>
#include <iostream>

namespace Benchmark {

Skippy::Skippy(char *theAddress): Benchmark(theAddress){
    lseek64(getFd(), 0, SEEK_SET);
}



void Skippy::execute(int iteration)
{
    lseek64(getFd(), (getSingleSector() * iteration), SEEK_CUR);
    write(getFd(), &buffer,  sizeof(buffer));
}


Skippy::~Skippy() {
}

}

