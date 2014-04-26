/*
 * JSONSerializer.h
 *
 *  Created on: Apr 16, 2014
 *      Author: cde
 */

#include <string>


#ifndef JSONSERIALIZER_H_
#define JSONSERIALIZER_H_

namespace HDDTest {

class JSONSerializer {
public:
	JSONSerializer();
	void addShort(std::string, short);
	void addLong(std::string, unsigned long);

	void addChar(std::string, char);
	void addStr(std::string, std::string);
	std::string getJson();
	virtual ~JSONSerializer();

protected:
	std::string jsonString;
};

} /* namespace HDDTest */

#endif /* JSONSERIALIZER_H_ */
