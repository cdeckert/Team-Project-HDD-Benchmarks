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

namespace HDDTest {

class HDDModePageReader {
private:
	std::string device;
	std::string deviceName;
	std::string vendor;
	std::string revision;

	std::string findValue(const char*, const char*);
public:
	HDDModePageReader(std::string);
	void read();
	std::string getDeviceName();
	std::string getVendor();
	~HDDModePageReader();
};

} /* namespace HDDTest */
#endif /* HDDMODEPAGEREADER_H_ */
