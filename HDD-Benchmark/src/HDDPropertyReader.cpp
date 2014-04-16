/*
 * HDDPropertyReader.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: cde
 */

#include "HDDPropertyReader.h"

namespace HDDTest {

HDDPropertyReader::HDDPropertyReader(std::string theAddress)
{
	this->fd = open64(theAddress.data(), O_RDONLY);
	perror("open");
}

void HDDTest::HDDPropertyReader::execute() {
	struct hd_geometry geom;
	if(ioctl(fd, HDIO_GETGEO, &geom) == 0)
	{
		std::cout << geom.sectors;
	}
}
HDDPropertyReader::~HDDPropertyReader() {
	// TODO Auto-generated destructor stub
}

} /* namespace HDDTest */
