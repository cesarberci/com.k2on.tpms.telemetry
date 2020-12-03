/*
 * DigitalIO.h
 *
 *  Created on: 31 de ago de 2019
 *      Author: cesar
 */

#ifndef DIGITALIO_H_
#define DIGITALIO_H_

#include <string>

enum _direction{
	OUT,
	IN
};

namespace src {

class DigitalIO {
public:
	DigitalIO(int pin, int dir);
	virtual ~DigitalIO();
	void set(void);
	void reset(void);
	void toggle(void);
	int value(void);
private:
	int pin;
	std::string direction;
	std::string f_direction;
	std::string f_value;
};

} /* namespace src */

#endif /* DIGITALIO_H_ */
