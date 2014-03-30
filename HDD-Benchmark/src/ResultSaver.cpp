/*
 * ResultSaver.cpp
 *
 *  Created on: 20.03.2014
 *      Author: chris
 */

#include "ResultSaver.h"

namespace HDDTest {


ResultSaver::ResultSaver(std::string drive, std::string testName) {
	this->drive = drive;
	this->testName = testName;
	this->iterations = 0;
}

ResultSaver::ResultSaver(std::string drive, std::string testName, long iterations) {
	this->drive = drive;
	this->testName = testName;
	this->iterations = iterations;
}

void ResultSaver::save(Stopwatch stopwatch) {
    std::ofstream csv;
    std::ofstream json;
    printf("\n\n");

    // cut of dir (example: /dev/sdb => sdb)
    unsigned int pos = drive.find_last_of("/\\");
    std::string driveName = drive.substr(pos+1);

    // generate filesnames
    std::string filename = std::string("results/result-") + driveName + "_" + testName;
        // only add iterations to filename if necessary
    if(iterations > 0) {
    	filename += "-" + std::to_string(iterations);
    }
    std::string filenamecsv = filename + ".csv";
    std::string filenamejsonp = filename + ".json";

    // open files and save data
    csv.open(filenamecsv);
    json.open(filenamejsonp);
    json << "{\"data\": [";
    for(int i=0; i < stopwatch.getSize(); i++)
    {
        json << stopwatch.getLapTime(i) << ",\n";
        csv << i << ", " << stopwatch.getLapTime(i)*1000 << "\n";
        printf("\rLines %10d                       \r", i);
    }
    csv.close();
    json << stopwatch.getLapTime(stopwatch.getSize()-1) << "], ";
    json << "\"testName\": \"" << testName << "\", ";
    json << "\"drive\": \"" << drive << "\"";
    json << "}";
    json.close();
}

ResultSaver::~ResultSaver() {
	// TODO Auto-generated destructor stub
}

} /* namespace HDDTest */
