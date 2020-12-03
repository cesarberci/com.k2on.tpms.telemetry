/*
 * Communication.cpp
 *
 *  Created on: 17 de ago de 2019
 *      Author: cesar
 */

#include "Communication.h"
#include "TpmsDefinitions.h"
#include "StringTools.h"

#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
#include <exception>
#include <thread>
#include <errno.h>      // Error number definitions

#include <iostream>

namespace src {

using namespace std;

Communication* Communication::uniqueInstance = 0;

static void run_reader(void);

Communication::Communication() {
	// TODO Auto-generated constructor stub
	this->receivedByte = 0;
	this->sd = 0;
	this->uniqueInstance = 0;
	this->dev = "/dev/ttyS0";
	this->running = false;
}

Communication::~Communication() {
	// TODO Auto-generated destructor stub
	running = false;
	while (!running) {
		//wait threads end.
	}
}

Communication* Communication::getInstance(void) {
	if (uniqueInstance == 0) {
		uniqueInstance = new Communication();
	}
	return uniqueInstance;
}

int src::Communication::connect(void) {
	struct termios tios;
	memset(&tios, 0, sizeof tios);
	speed_t speed;
	sd = open(dev.c_str(), O_RDWR | O_NOCTTY | O_ASYNC);
	if (sd <= 0) {
		cout << "Error: (" << strerror(errno) << "). Trying to open serial port"
				<< endl; // @suppress("Symbol is not resolved")
		throw "Cannot configure serial port!";
	}
	tcgetattr(sd, &tios);
	speed = B9600;
	if ((cfsetispeed(&tios, speed) < 0) || (cfsetospeed(&tios, speed) < 0)) {
		close(sd);
		sd = -1;
		cout << "Error: (" << strerror(errno)
				<< "). Trying to set serial port speed" << endl; // @suppress("Symbol is not resolved")
		throw "Cannot configure serial port speed";
	}
	cfmakeraw(&tios);

	/* C_CFLAG      Control options
	 CLOCAL       Local line - do not change "owner" of port
	 CREAD        Enable receiver
	 */
	tios.c_cflag |= (CREAD | CLOCAL);
	/*
	 VMIN         Minimum number of characters to read
	 VTIME        Time to wait for data (tenths of seconds)
	 */
	tios.c_cc[VMIN] = 1;
	tios.c_cc[VTIME] = 1;

	tcflush(sd, TCIOFLUSH);
	if (tcsetattr(sd, TCSANOW, &tios) < 0) {
		close(sd);
		sd = -1;
		cout << "Error: (" << strerror(errno)
				<< "). Trying to configure serial port" << endl; // @suppress("Symbol is not resolved")
		throw "Cannot configure serial port!";
	}

	tcflush(sd, TCIOFLUSH);
	return 0;
}

unsigned char Communication::getByte() {
	return receivedByte;
}

unsigned char * Communication::getBytePointer() {
	return &receivedByte;
}

void Communication::start(void) {
	try {
		connect();
		running = true;
		thread t(run_reader); // @suppress("Type cannot be resolved")
		t.detach(); // @suppress("Method cannot be resolved")
		cout << "running at: " << dev << endl;
		writeStr(&HANDSHAKE[0], sizeof HANDSHAKE);
	} catch (const char* e) {
		cout << "Error: cannot start communication, exiting..." << endl;
		exit(0);
	} catch (exception &e) {
		cout << "Error: cannot start communication, exiting..." << endl;
		exit(0);
	}
}

int Communication::getSerialDescriptor() const {
	return sd;
}

void Communication::setSerialDescriptor(int sd) {
	this->sd = sd;
}

void Communication::writeStr(const unsigned char * s, unsigned int size) {
	write(sd, s, size);
}

void Communication::setDev(string dev) {
	this->dev = dev;
}

#include <stdio.h>
void run_reader(void) {
	Communication * comm = Communication::getInstance();
	unsigned char * b = comm->getBytePointer();
	int t;
	while (comm->running) {
		t = read(comm->getSerialDescriptor(), b, 1);
		if (t > 0) {
			comm->notify();
		}
		if (t == -1)
			cout << "Error " << strerror(errno) << " from tcsetattr" << endl; // @suppress("Symbol is not resolved")

	}
	comm->running = true;
	return;
}

}

