/*
 * TpmsHandShake.cpp
 *
 *  Created on: 15 de ago de 2019
 *      Author: cesar
 */

#include "TpmsHandShake.h"
#include "TpmsDefinitions.h"

namespace src {

TpmsHandShake::TpmsHandShake() {
	// TODO Auto-generated constructor stub
	handshake = false;
}

TpmsHandShake::~TpmsHandShake() {
	// TODO Auto-generated destructor stub
}

int TpmsHandShake::decompose(TpmsRawData* rawData) {
	if (rawData->getFunctionNumber() == HANDSHAKE_SIGNAL) {
		handshake = true;
		return 0;
	} else
		handshake = false;
	return -1;
}

bool TpmsHandShake::isHandShake(void) {
	return handshake;
}

} /* namespace src */
