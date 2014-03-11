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
    Skippy(char*);
    void execute(int);
    virtual ~Skippy();
    char buffer[1024];
    int fd;
    
private:

};
}
#endif	/* SKIPPY_H */

