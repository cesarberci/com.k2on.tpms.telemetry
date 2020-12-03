/*
 * Communication.h
 *
 *  Created on: 17 de ago de 2019
 *      Author: cesar
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include "Observeble.h"

// Include from Include stereotype (header)
#include "Pkg_src.h"
// End of Include stereotype (header)

namespace src {

/**
 * Pattern: Singleton
 */
class Communication : public Observeble{
public:
	static Communication * getInstance(void);
	virtual ~Communication();
	unsigned char getByte();
	unsigned char * getBytePointer();
	void start(void);
	int getSerialDescriptor() const;
	void setSerialDescriptor(int sd);
	void setDev(std::string dev);
	void writeStr(const unsigned char * s,unsigned int size);
	bool running;
private:
	Communication();
	int connect(void);
	static Communication * uniqueInstance;
	unsigned char receivedByte;
	int sd;
	std::string dev;
};

} /* namespace src */

#endif /* COMMUNICATION_H_ */
