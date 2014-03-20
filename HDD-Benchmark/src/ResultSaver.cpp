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

    std::stringstream filename;
    filename << "results/"<< "result" << drive << "_" << testName << "-" << iterations;
    std::stringstream filenamecsv;
    filenamecsv << filename << ".csv";
    std::stringstream filenamejsonp;
    filenamejsonp << filename << ".jsonp";
    csv.open(filenamecsv.str().c_str());
    jsonp.open(filenamejsonp.str().c_str());
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
