/*
 * ResultSaver.cpp
 *
 *  Created on: 20.03.2014
 *      Author: chris
 */

#include "ResultSaver.h"

namespace HDDTest {

ResultSaver::ResultSaver(Benchmark::Benchmark* benchmark) {
	this->benchmark = benchmark;
}
/*ResultSaver::ResultSaver(std::string drive, std::string testName) {
	this->drive = drive;
	this->testName = testName;
	this->iterations = 0;
}

ResultSaver::ResultSaver(std::string drive, std::string testName, long iterations) {
	this->drive = drive;
	this->testName = testName;
	this->iterations = iterations;
}*/


void ResultSaver::save(Stopwatch stopwatch) {
    std::ofstream csv;
    std::ofstream json;
    printf("\n\n");

    // read properties
    HDDPropertyReader propReader = HDDPropertyReader(benchmark->getDevice());
    propReader.execute();

    // read mode pages
    HDDTest::HDDModePageReader modePageReader = HDDTest::HDDModePageReader(benchmark->getDevice());
    modePageReader.read();

    // cut of dir (example: /dev/sdb => sdb)
    unsigned int pos = benchmark->getDevice().find_last_of("/\\");
    std::string driveName = benchmark->getDevice().substr(pos+1);

    // get name of HDD
    HDDTest::HDDModePageReader HDDModePageReader1 = HDDTest::HDDModePageReader(benchmark->getDevice());
    HDDModePageReader1.read();

    // generate filesnames
    std::string filename = std::string("results/result-") + HDDModePageReader1.getVendor() + "-" + HDDModePageReader1.getDeviceName() + "-" + benchmark->getResultName(); //
    std::string filenamecsv = filename + ".csv";
    std::string filenamejsonp = filename + ".json";
    std::cout << "filename: " << filename << "\n";

    // open files and save data
    csv.open(filenamecsv);
    json.open(filenamejsonp);
    json << "{\"data\": [";
    for(unsigned int i=0; i < stopwatch.getSize(); i++)
    {
        json << stopwatch.getLapTime(i) << ",\n";
        csv << i << ", " << stopwatch.getLapTime(i)*1000 << "\n";
        printf("\rLines %10d                       \r", i);
    }
    csv.close();
    json << stopwatch.getLapTime(stopwatch.getSize()-1) << "], ";
    json << "\"testName\": \"" << benchmark->getTestName() << "\", ";
    json << "\"drive\": \"" << benchmark->getDevice() << "\",";
    json << "\"vendor\": \"" << HDDModePageReader1.getVendor() << "\",";
    json << "\"deviceName\": \"" << HDDModePageReader1.getDeviceName() << "\",";
    json << "\"properties\": " << propReader.getJson() << "\",";;
    json << "\"modePages\": " << modePageReader.getJson();
    json.close();
}

ResultSaver::~ResultSaver() {
	// TODO Auto-generated destructor stub
}

} /* namespace HDDTest */
