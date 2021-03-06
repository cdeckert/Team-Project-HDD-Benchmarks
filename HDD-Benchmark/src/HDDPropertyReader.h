/*
 * HDDPropertyReader.h
 *
 *  Created on: Apr 16, 2014
 *      Author: cde
 */


#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <iostream>

#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/hdreg.h>
#include "JSONSerializer.h"


#ifndef HDDPROPERTYREADER_H_
#define HDDPROPERTYREADER_H_



namespace HDDTest {

class HDDPropertyReader {
public:
	HDDPropertyReader(std::string);
	void execute();
	std::string getJson();
	virtual ~HDDPropertyReader();
private:
	int fd;
	JSONSerializer json;

};


} /* namespace HDDTest */

#endif /* HDDPROPERTYREADER_H_ */
