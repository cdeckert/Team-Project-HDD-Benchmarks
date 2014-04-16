/*
 * HDDPropertyReader.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: cde
 */

#include "HDDPropertyReader.h"
#include "JSONSerializer.h"

namespace HDDTest {

HDDPropertyReader::HDDPropertyReader(std::string theAddress)
{
	this->fd = open64(theAddress.data(), O_RDONLY);
	perror("open");
}

void HDDTest::HDDPropertyReader::execute() {
	JSONSerializer json = JSONSerializer();
	struct hd_geometry geom;



	if(ioctl(fd, HDIO_GETGEO, &geom) == 0)
	{
		json.addChar("hd_geometry.heads", geom.heads);
		json.addChar("hd_geometry.sectors", geom.sectors);
		json.addLong("hd_geometry.start", geom.start);
		json.addShort("hd_geometry.cylinders", geom.cylinders);
	}
	std::cout << json.getJson() << "\n";
}
HDDPropertyReader::~HDDPropertyReader() {
	// TODO Auto-generated destructor stub
}

} /* namespace HDDTest */
