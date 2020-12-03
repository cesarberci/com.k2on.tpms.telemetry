/*
 * DigitalIO.cpp
 *
 *  Created on: 31 de ago de 2019
 *      Author: cesar
 */

#include "DigitalIO.h"

#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <exception>
#include <fstream>

#define GPIO_PATH "/sys/class/gpio"

namespace src {

using namespace std;

DigitalIO::DigitalIO(int pin, int dir) {
	// TODO Auto-generated constructor stub
	this->pin = pin;
	this->direction = (dir == OUT) ? "out" : "in";
	stringstream f_dir;
	f_dir << GPIO_PATH << "/gpio" << pin << "/direction";
	this->f_direction = f_dir.str();
	stringstream f_val;
	f_val << GPIO_PATH << "/gpio" << pin << "/value";
	this->f_value = f_val.str();
	try {
		stringstream str;
		str << GPIO_PATH << "/export";
		ofstream create_f(str.str(), ios::out);
		create_f << pin;
		create_f.close();
		ofstream direction_f(f_direction, ios::out);
		direction_f << this->direction;
		direction_f.close();
	} catch (exception &e) {
		throw invalid_argument("Digital IO: Cannot open port");
	}
}

DigitalIO::~DigitalIO() {
	// TODO Auto-generated destructor stub
}

void DigitalIO::set(void) {
	ofstream f(this->f_value, ios::out);
	f << 1;
	f.close();
}

void DigitalIO::reset(void) {
	ofstream f(this->f_value, ios::out);
	f << 0;
	f.close();
}

void DigitalIO::toggle(void) {
	if (value()==0)
		set();
	else
		reset();
}

int DigitalIO::value(void) {
	ifstream f(this->f_value, ios::in);
	int r;
	f >> r;
	f.close();
	return r;
}

} /* namespace src */

