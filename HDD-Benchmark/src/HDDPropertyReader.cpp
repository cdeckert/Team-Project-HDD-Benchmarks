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
	json = HDDTest::JSONSerializer();
}

void HDDTest::HDDPropertyReader::execute() {
	struct hd_geometry geom;
	long valLong;
	unsigned char identity[512];
	std::string s;

	// https://www.kernel.org/doc/Documentation/ioctl/hdio.txt
	if(ioctl(fd, HDIO_GETGEO, &geom) == 0)
	{
		json.addChar("hd_geometry.heads", geom.heads);
		json.addChar("hd_geometry.sectors", geom.sectors);
		json.addLong("hd_geometry.start", geom.start);
		json.addShort("hd_geometry.cylinders", geom.cylinders);
	}

	ioctl(fd, HDIO_GET_UNMASKINTR, &valLong);
	json.addLong("HDIO_GET_UNMASKINTR", valLong);

	ioctl(fd, HDIO_GET_MULTCOUNT, &valLong);
	json.addLong("HDIO_GET_MULTCOUNT", valLong);

	ioctl(fd, HDIO_GET_IDENTITY, &identity);
	s.assign((char*)&identity[0], sizeof(identity));
	//json.addStr("HDIO_GET_IDENTITY", s);


	ioctl(fd, HDIO_GET_KEEPSETTINGS, &valLong);
	json.addLong("HDIO_GET_KEEPSETTINGS", valLong);

	ioctl(fd, HDIO_GET_32BIT, &valLong);
	json.addLong("HDIO_GET_32BIT", valLong);

	ioctl(fd, HDIO_GET_NOWERR, &valLong);
	json.addLong("HDIO_GET_NOWERR", valLong);


	ioctl(fd, HDIO_GET_DMA, &valLong);
	json.addLong("HDIO_GET_DMA", valLong);


	ioctl(fd, HDIO_GET_NICE, &valLong);
	json.addLong("HDIO_GET_NICE", valLong);

	ioctl(fd, HDIO_GET_WCACHE, &valLong);
	json.addLong("HDIO_GET_WCACHE", valLong);

	ioctl(fd, HDIO_GET_ACOUSTIC, &valLong);
	json.addLong("HDIO_GET_ACOUSTIC", valLong);


	ioctl(fd, HDIO_GET_ADDRESS, &valLong);
	json.addLong("HDIO_GET_ADDRESS", valLong);


	ioctl(fd, HDIO_GET_BUSSTATE, &valLong);
	json.addLong("HDIO_GET_BUSSTATE", valLong);


	//std::cout << json.getJson() << "\n";
}

std::string HDDTest::HDDPropertyReader::getJson()
{
	return json.getJson();
}

HDDPropertyReader::~HDDPropertyReader() {
	// TODO Auto-generated destructor stub
}

} /* namespace HDDTest */
