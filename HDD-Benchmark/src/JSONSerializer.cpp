/*
 * JSONSerializer.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: cde
 */

#include "JSONSerializer.h"

namespace HDDTest {

JSONSerializer::JSONSerializer() {
	// TODO Auto-generated constructor stub
	jsonString = '{';
}



void JSONSerializer::addShort(std::string key, short value)
{
	if(jsonString != "{")
	{
		jsonString+= ",";
	}
	jsonString += "\""+key+"\":"+std::to_string(value);
}

void JSONSerializer::addLong(std::string key, unsigned long value)
{
	if(jsonString != "{")
	{
		jsonString+= ",";
	}
	jsonString += "\""+key+"\":"+std::to_string(value);
}

void JSONSerializer::addChar(std::string key, char value)
{
	if(jsonString != "{")
	{
		jsonString+= ",";
	}
	jsonString += "\""+key+"\":\""+std::to_string(value)+"\"";
}

void JSONSerializer::addStr(std::string key, std::string value)
{
	if(jsonString != "{")
	{
		jsonString+= ",";
	}
	size_t pos = 0;
	if(((pos = value.find('"', pos)) != std::string::npos))
	{
		value.replace(pos, value.length(), "''");
	}

	jsonString += "\""+key+"\":\""+value+"\"";
}


std::string JSONSerializer::getJson()
{
	jsonString+="}";
	return jsonString;
}


JSONSerializer::~JSONSerializer() {
	// TODO Auto-generated destructor stub
}

} /* namespace HDDTest */
