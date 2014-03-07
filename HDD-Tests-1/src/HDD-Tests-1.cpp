//============================================================================
// Name        : HDD-Tests-1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================



#include <iostream>

#include "Stopwatch.h"

int main() {


	Stopwatch* stopwatch = new Stopwatch();

	stopwatch->start();
	for(int i=0; i<10;i++)
	{
		std::cout << i<< "\n";
		stopwatch->lap();
	}

	stopwatch->stop();

	for(int i=0; i<10; i++)
	{
		std::cout << i << ":" << stopwatch->getLapTime(i) << "\n";
	}
	std::cout << "Total: "<< stopwatch->getTotalTime() << "\n";


	return 0;
}
