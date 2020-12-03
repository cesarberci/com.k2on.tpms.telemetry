/*
 * TpmsDevice.h
 *
 *  Created on: 17 de ago de 2019
 *      Author: cesar
 */

#ifndef TPMSDEVICE_H_
#define TPMSDEVICE_H_

#include "Observer.h"

// Include from Include stereotype (header)
#include "Pkg_src.h"
// End of Include stereotype (header)

#include "Communication.h"
#include "TpmsRawData.h"

namespace src {

class TpmsDevice: public Observer {
public:
	TpmsDevice();
	virtual ~TpmsDevice();
	void update();
private:
	Communication * comm;
	TpmsRawData * rawMsg;
};

} /* namespace src */

#endif /* TPMSDEVICE_H_ */
