/*
 * TpmsData.h
 *
 *  Created on: 15 de ago de 2019
 *      Author: cesar
 *
 *      Interface class to define all data types in tmps protocol
 */

#ifndef TPMSDATA_H_
#define TPMSDATA_H_

// Include from Include stereotype (header)
#include "Pkg_src.h"
// End of Include stereotype (header)

#include "TpmsRawData.h"

namespace src {

enum _function_numbers{
	HANDSHAKE_SIGNAL = 0x11,
	ALERT_PARAMETERS_TRANSMISSION = 0x62,
	TIRE_DATA_TRANSMISSION = 0x63,
	SEND_TRAILER_ID = 0x64,
	DELETE_CODED_SENSOR_ID = 0x65,
	TPMS_SENSORS_ID_LEARNING = 0x66,
	FMS_REQUEST_TPMS_MODULE_TO_SEND_THE_TRAILER_DATA_TO_REPEATER = 0x67,
	REPEATER_BATTERY_VOLTAGE_STATUS = 0x68
};

enum _data_state {
	MESSAGE_DATA_NOT_LOADED,
	MESSAGE_DATA_OK,
	MESSAGE_DECODE_FAIL
};


class TpmsData {
public:
	TpmsData();
	virtual ~TpmsData();
	virtual int decompose(TpmsRawData * rawData) = 0;
	bool isTireData(void);
	bool isBatteryStatus(void);
	bool isNumberOfTires(void);
	bool isUpdateConfirm(void);
	bool isHandShake(void);
	bool isNoTireData(void);
	bool isInvalidData(void);
	bool isBaterryStatus(void);
};

} /* namespace src */

#endif /* TPMSDATA_H_ */
