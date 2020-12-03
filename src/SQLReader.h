/*
 * SQLReader.h
 *
 *  Created on: 28 de fev de 2020
 *      Author: cesar
 */

#ifndef SQLREADER_H_
#define SQLREADER_H_

#include <sstream>


namespace src {

class SQLReader {
public:
	virtual ~SQLReader();
	static SQLReader * getInstance(void);
	void sendRequest(std::stringstream * request, void * callback);
private:
	SQLReader();
	static SQLReader * instance;
};

} /* namespace src */

#endif /* SQLREADER_H_ */
