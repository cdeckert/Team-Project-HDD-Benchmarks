/*
 * ResultSaver.cpp
 *
 *  Created on: 20.03.2014
 *      Author: chris
 */

#include "ResultSaver.h"

namespace HDDTest {


ResultSaver::ResultSaver(std::string drive, std::string testName, long iterations) {
	this->drive = drive;
	this->testName = testName;
	this->iterations = iterations;
}

void ResultSaver::save(Stopwatch stopwatch) {
    std::ofstream csv;
    std::ofstream jsonp;
    printf("\n\n");

    std::string filename = std::string("results/result") + drive + "_" + testName + "-" + std::to_string(iterations);
    std::string filenamecsv = filename + ".csv";
    std::string filenamejsonp = filename + ".jsonp";
    csv.open(filenamecsv);
    jsonp.open(filenamejsonp);
    jsonp << "data = [";
    for(int i=0; i < stopwatch.getSize(); i++)
    {
        jsonp << stopwatch.getLapTime(i) << ", ";
        csv << i << ", " << stopwatch.getLapTime(i)*1000 << "\n";
        printf("\rLines %10d                       \r", i);
    }
    csv.close();
    jsonp << stopwatch.getLapTime(stopwatch.getSize()-1) << "];";
    jsonp.close();
}

ResultSaver::~ResultSaver() {
	// TODO Auto-generated destructor stub
}

} /* namespace HDDTest */
