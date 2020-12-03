/*
 * StringTools.h
 *
 *  Created on: 19 de jun de 2019
 *      Author: cesar
 */

#include <string>
#include <vector>

#ifndef SRC_GEN_MODBUSMANAGER_UTILS_STRINGTOOLS_H_
#define SRC_GEN_MODBUSMANAGER_UTILS_STRINGTOOLS_H_

using namespace std;

class StringTools {
public:
	StringTools();
	virtual ~StringTools();
	static string toHexString(char * buf, int len);
	static string toHexString(string buf);
	static string toHexString(vector<char> buf);
};

#endif /* SRC_GEN_MODBUSMANAGER_UTILS_STRINGTOOLS_H_ */
