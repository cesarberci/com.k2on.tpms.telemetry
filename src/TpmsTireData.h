/*
 * TpmsTireData.h
 *
 *  Created on: 15 de ago de 2019
 *      Author: cesar
 */

#ifndef TPMSTIREDATA_H_
#define TPMSTIREDATA_H_

#include "string"
#include "stdint.h"
#include "TpmsData.h"

struct _tire_status {
	uint8_t SENSOR_BATTERY_STATUS :1;
	uint8_t RECEIVING_OK :1;
	uint8_t reserved :1;
	uint8_t HIGH_PRESSURE_ALARM :1;
	uint8_t LOW_PRESSURE_ALARM :1;
	uint8_t HIGH_TEMPERATURE :1;
	uint8_t FAST_LEAKAGE_ALERT :1;
	uint8_t SLOW_LEAKAGE_ALERT :1;
};

typedef union TIRE_STATUS {
	uint8_t all;
	struct _tire_status type;
} TireStatus;

typedef enum _pressure_units {
	BAR, PSI
} PRESSURE_UNIT;

namespace src {

class TpmsTireData: public TpmsData {
public:
	TpmsTireData();
	TpmsTireData(TpmsRawData * rawData);
	virtual ~TpmsTireData();
	TireStatus getTireStatus(void);
	uint8_t getIntTireStatus(void);
	int decompose(TpmsRawData * rawData);
	float getPressure(PRESSURE_UNIT unit);
	uint16_t getIntPressure(void);
	int getTemperature(void);
	bool isTireData(void);
	bool isNumberOfTires(void);
	bool isUpdateConfirm(void);
	bool isNoTireData(void);
	bool isInvalidData(void);
	bool isBaterryStatus(void);
	int getNumberOfTires() const;
	int getSensorId() const;
	int getTirePosition() const;
	int getTrailerPosition() const;
	int getBaterryStatusAt(int trailer);
	std::string getStatusString(void);
private:
	uint8_t batteryStatus[6];
	uint8_t state;
	uint8_t trailerPosition;
	uint8_t tirePosition;
	uint32_t sensorID;
	uint16_t pressure;
	uint16_t temperature;
	TireStatus status;
	uint8_t numberOfTires;
	bool tireData;
	bool repeaterBateryStatus;
	bool noTireData;
	bool updateConfirm;
	bool nTires;
	bool dataError;

	void decodeDataByte(std::vector<uint8_t>* data);
	void stateClean();

};

} /* namespace src */

#endif /* TPMSTIREDATA_H_ */
