/*
 * StringTools.cpp
 *
 *  Created on: 19 de jun de 2019
 *      Author: cesar
 */
#include <sstream>

#include "StringTools.h"

StringTools::StringTools() {
	// TODO Auto-generated constructor stub

}

StringTools::~StringTools() {
	// TODO Auto-generated destructor stub
}

string StringTools::toHexString(char * buf, int len) {
	stringstream ss;
	ss.str("");
	char buffer[4];
	for (int i = 0; i < len; i++) {
		sprintf(buffer, "%X ", *buf);
		buf++;
		ss << buffer;
	}
	return ss.str();
}

string StringTools::toHexString(string buf) {
	stringstream ss;
	ss.str("");
	char buffer[4];
	for (size_t i = 0; i < buf.length(); i++) {
		sprintf(buffer, "%X ", buf.at(i));
		ss << buffer;
	}
	return ss.str();
}

string StringTools::toHexString(vector<char> buf) {
	stringstream ss;
	ss.str("");
	char buffer[4];
	for (size_t i = 0; i < buf.size(); i++) {
		sprintf(buffer, "%X ", buf[i]);
		ss << buffer;
	}
	return ss.str();
}
