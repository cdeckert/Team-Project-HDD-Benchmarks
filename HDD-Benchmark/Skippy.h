/* 
 * File:   Skippy.h
 * Author: christiandeckert
 *
 * Created on March 8, 2014, 8:35 PM
 */

#ifndef SKIPPY_H
#define	SKIPPY_H

#include "Benchmark.h"

namespace Benchmark {

class Skippy : public Benchmark {
public:
    Skippy(std::string);
    void configure(int);
    void runIteration(int);
    void execute();
    virtual ~Skippy();
    char buffer[1024];
    
    int getFd();
    int getSingleSector();

private:
    int iterations;
    int fd;
    int SINGLE_SECTOR;
};
}
#endif	/* SKIPPY_H */

