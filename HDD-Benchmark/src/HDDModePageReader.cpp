/*
 * HDDModePageReader.cpp
 *
 *  Created on: 25.07.2014
 *      Author: chris
 */

#include "HDDModePageReader.h"

namespace HDDTest {

HDDModePageReader::HDDModePageReader(std::string device) {
	this->device = device;
}

void HDDModePageReader::read() {
	std::string cmd = std::string("sginfo -A ") + device;
	FILE* pipe = popen(cmd.c_str(), "r");
	if (!pipe) return;
	char buffer[128];
	std::string result = "";
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);

	// save relevant data
	vendor = std::string(findValue(std::string("Vendor").c_str(), result.c_str()));
	deviceName = std::string(findValue(std::string("Product").c_str(), result.c_str()));
	revision = findValue(std::string("Revision level").c_str(), result.c_str());
}

std::string HDDModePageReader::findValue(const char* valueName, const char* str) {
	const char* first = strstr(str, valueName); // first char of row
	const char* last = strchr(first, '\n'); // last char of row
	char line[64];
	char resultName[33] = {0};
	char resultValue[33] = {0};

	if(strncpy(line, first, (last-first)) == nullptr) { // copy line to new variable
		return nullptr; // did not find occurrence
	}

	if(strstr(line, "Device Type") != nullptr || strstr(line, "Vendor") != nullptr || strstr(line, "Product") != nullptr || strstr(line, "Revision level") != nullptr) {
		// divide after 28 chars
		strncpy(resultName, line, 27);
		strncpy(resultValue, line+27, 32);
	} else {
		// divide after 32 chars
		strncpy(resultName, line, 31);
		strncpy(resultValue, line+31, 32);
	}

	// trim values TODO NOT WORKING
	for(int i = 32; i >= 0; i--) {
		if(resultName[i] == ' ' || resultName[i] == '\0'  || resultName[i] == '\n')
			resultName[i] = '\0';
		else
			break;
	}
	for(int i = 32; i >= 0; i--) {
		if(resultValue[i] == ' ' || resultValue[i] == '\0' || resultValue[i] == '\n')
			resultValue[i] = '\0';
		else
			break;
	}

	return resultValue;
}

std::string HDDModePageReader::getDeviceName() {
	// trim from both ends
	return deviceName;
}

std::string HDDModePageReader::getVendor() {
	return vendor;
}

HDDModePageReader::~HDDModePageReader() {
	// TODO Auto-generated destructor stub
}

} /* namespace HDDTest */
