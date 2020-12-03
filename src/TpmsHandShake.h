/*
 * TpmsHandShake.h
 *
 *  Created on: 15 de ago de 2019
 *      Author: cesar
 */

#ifndef TPMSHANDSHAKE_H_
#define TPMSHANDSHAKE_H_

#include "TpmsData.h"

namespace src {

class TpmsHandShake: public TpmsData {
public:
	TpmsHandShake();
	virtual ~TpmsHandShake();
	int decompose(TpmsRawData * rawData);
	bool isHandShake(void);
private:
	bool handshake;
};

} /* namespace src */

#endif /* TPMSHANDSHAKE_H_ */
