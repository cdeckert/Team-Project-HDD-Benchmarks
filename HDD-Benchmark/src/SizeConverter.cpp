/*
 * SizeConverter.cpp
 *
 *  Created on: 16.04.2014
 *      Author: chris
 */

#include "SizeConverter.h"

namespace HDDTest {

SizeConverter::SizeConverter() {
	// TODO Auto-generated constructor stub

}

SizeConverter::~SizeConverter() {
	// TODO Auto-generated destructor stub
}

std::string SizeConverter::convertBytesToHumanReadable(unsigned int bytes) {
	char res[15];
	if(bytes / 1024 == 0) {
		sprintf(res, "%.0fB", bytes*1.0);
	} else if(bytes / (1024*1024) == 0) {
		sprintf(res, "%.0fKB", bytes*1.0/1024);
	} else if(bytes / (1024*1024*1024) == 0) {
		sprintf(res, "%.0fMB", bytes*1.0/(1024*1024));
	} else {
		sprintf(res, "%.0fGB", bytes*1.0/(1024*1024*1024));
	}
	return res;
}

} /* namespace HDDTest */
