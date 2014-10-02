/*
 * HDDModePageReader.cpp
 *
 *  Created on: 25.07.2014
 *      Author: chris
 */

#include "HDDModePageReader.h"

namespace HDDTest
{

HDDModePageReader::HDDModePageReader(std::string device)
{
	this->device = device;
}

void HDDModePageReader::read()
{
	parameterList = std::vector<struct KeyValuePair>();

	std::string cmd = std::string("sginfo -A ") + device;
	FILE *pipe = popen(cmd.c_str(), "r");
	if (!pipe) return;
	char buffer[128];
	std::string result = "";
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);

	// split result by line and save each line in resultLines
	std::vector<std::string> resultLines = std::vector<std::string>();

	size_t curStart = 0;
	size_t pos = result.find_first_of('\n', curStart);
	while (pos < result.length())
	{
		resultLines.push_back(result.substr(curStart, pos - curStart));
		curStart = pos + 1;
		pos = result.find_first_of('\n', curStart);
	}

	// extract information
	for (unsigned long long int i = 0; i < resultLines.size(); i++)
	{
		if (resultLines[i].empty())
		{
			continue;
		}
		else if (resultLines[i + 1].find("-----", 0) != std::string::npos || resultLines[i].find("-----", 0) != std::string::npos)
		{
			continue;
		}
		else
		{
			struct KeyValuePair newPair;

			if (resultLines[i].find("Vendor", 0) != std::string::npos || resultLines[i].find("Product", 0) != std::string::npos || resultLines[i].find("Revision level", 0) != std::string::npos)
			{
				// divide after 28 chars
				newPair.key = resultLines[i].substr(0, 27);
				newPair.value = resultLines[i].substr(27, 36);
			}
			else if (resultLines[i].find("Serial Number", 0) != std::string::npos)
			{
				// divide after 16 chars
				newPair.key = resultLines[i].substr(0, 15);
				newPair.value = resultLines[i].substr(15, 36);
			}
			else
			{
				// divide after 32 chars
				newPair.key = resultLines[i].substr(0, 35);
				newPair.value = resultLines[i].substr(35, 36);
			}
			trimValue(&newPair.key);
			trimValue(&newPair.value);

			// save most relevant data seperately
			if (newPair.key.find("Vendor") != std::string::npos)
			{
				vendor = newPair.value;
			}
			else if (newPair.key.find("Product") != std::string::npos)
			{
				deviceName = newPair.value;
			}
			else if (newPair.key.find("Revision level") != std::string::npos)
			{
				revision = newPair.value;
			}
			parameterList.push_back(newPair);
		}
	}
}

void HDDModePageReader::trimValue(std::string *text)
{
	for (int i = text->size() - 1; i >= 0; i--)
	{
		if ((*text)[i] == ' ' || (*text)[i] == '\0' || (*text)[i] == '\n' || !(('a' <= (*text)[i] && (*text)[i] < 'z') || ('A' <= (*text)[i] && (*text)[i] < 'Z') || ('0' <= (*text)[i] && (*text)[i] < '9') || (*text)[i] == ')' || (*text)[i] == ']' || (*text)[i] == '-'))
			(*text).erase(i, std::string::npos);
		else
			break;
	}
}

std::string HDDModePageReader::getDeviceName()
{
	return deviceName;
}

std::string HDDModePageReader::getVendor()
{
	return vendor;
}

/*std::string HDDModePageReader::getJson() {
    HDDTest::JSONSerializer json = HDDTest::JSONSerializer();

    for(unsigned long long int i = 0; i < parameterList.size(); i++) {
        json.addStr(parameterList[i].key, parameterList[i].value);
    }

    return json.getJson();
}*/

HDDModePageReader::~HDDModePageReader()
{
	// TODO Auto-generated destructor stub
}

} /* namespace HDDTest */
