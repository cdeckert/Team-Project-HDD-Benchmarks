/*
 * HDDModePageReader.h
 *
 *  Created on: 25.07.2014
 *      Author: chris
 */

#ifndef HDDMODEPAGEREADER_H_
#define HDDMODEPAGEREADER_H_

#include <string.h>
#include <iostream>
#include <stdio.h>
#include "JSONSerializer.h"
#include <vector>

namespace HDDTest {

struct KeyValuePair {
	std::string key;
	std::string value;
};


class HDDModePageReader {
private:
	std::string device;
	std::string deviceName;
	std::string vendor;
	std::string revision;
	std::vector<struct KeyValuePair> parameterList;

	//std::string findValue(const char*, const char*);
	void trimValue(std::string*);
public:
	HDDModePageReader(std::string);
	void read();
	std::string getDeviceName();
	std::string getVendor();
	std::string getJson();
	~HDDModePageReader();
};

} /* namespace HDDTest */
#endif /* HDDMODEPAGEREADER_H_ */
