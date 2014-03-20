/*
 * ResultSaver.h
 *
 *  Created on: 20.03.2014
 *      Author: chris
 */

#ifndef RESULTSAVER_H_
#define RESULTSAVER_H_

#include <time.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <Stopwatch.h>

namespace HDDTest {

class ResultSaver {
private:
	std::string drive;
	std::string testName;
	long iterations;
public:
	ResultSaver(std::string, std::string, long);
	//void save(std::vector<double>);
	void save(Stopwatch);
	~ResultSaver();
};

} /* namespace HDDTest */
#endif /* RESULTSAVER_H_ */
