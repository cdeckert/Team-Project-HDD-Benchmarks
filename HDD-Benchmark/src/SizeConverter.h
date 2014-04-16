/*
 * SizeConverter.h
 *
 *  Created on: 16.04.2014
 *      Author: chris
 */

#ifndef SIZECONVERTER_H_
#define SIZECONVERTER_H_

#include <string>

namespace HDDTest {

class SizeConverter {
	SizeConverter();
	~SizeConverter();
public:
	static std::string convertBytesToHumanReadable(unsigned int);
};

} /* namespace HDDTest */
#endif /* SIZECONVERTER_H_ */
