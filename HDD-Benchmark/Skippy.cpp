/* 
 * File:   Skippy.cpp
 * Author: christiandeckert
 * 
 * Created on March 8, 2014, 8:35 PM
 */

#include "Skippy.h"

#include <stdio.h>

Skippy::Skippy(char *theAddress): Benchmark(theAddress){
    
}



void Skippy::execute(int iteration)
{
    char buffer[1024];
	
    
    lseek64(getFd(), (getSingleSector() * iteration), SEEK_CUR);
    write(getFd(), &buffer, 1024);
    perror("write");

        
}


Skippy::~Skippy() {
}

