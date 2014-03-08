/* 
 * File:   Skippy.cpp
 * Author: christiandeckert
 * 
 * Created on March 8, 2014, 8:35 PM
 */

#include "Skippy.h"

#include <stdio.h>

Skippy::Skippy(char *theAddress): Benchmark(theAddress){}



void Skippy::execute(int iteration)
{
        
	lseek64(getFd(), (SINGLE_SECTOR * iteration), SEEK_CUR);
        //perror("Seek");
        std::cout << sizeof(buffer) << "\n";
        write(fd, &buffer, sizeof(buffer));
        
        //perror("Write");
}


Skippy::~Skippy() {
}

