/*
 * System.h
 *
 *  Created on: 6 de ago de 2019
 *      Author: César Daltoé Berci
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "src/Pkg_src.h"

#include "src/version_num.h"

const unsigned char completeVersion[] = { 'R', '-',
VERSION_MAJOR_INIT, '.',
VERSION_MINOR_INIT, '-', 'D', '-',
BUILD_DAY_CH0, BUILD_DAY_CH1, '/',
BUILD_MONTH_CH0, BUILD_MONTH_CH1, '/',
BUILD_YEAR_CH0, BUILD_YEAR_CH1, BUILD_YEAR_CH2, BUILD_YEAR_CH3, '-', 'T', '-',
BUILD_HOUR_CH0, BUILD_HOUR_CH1, ':',
BUILD_MIN_CH0, BUILD_MIN_CH1, ':',
BUILD_SEC_CH0, BUILD_SEC_CH1, '\0' };

namespace src {

class System {
public:
	System();
	~System();
private:
};

}
#endif /* SYSTEM_H_ */
