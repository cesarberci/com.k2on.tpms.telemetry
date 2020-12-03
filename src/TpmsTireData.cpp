/*
 * TpmsTireData.cpp
 *
 *  Created on: 15 de ago de 2019
 *      Author: cesar
 */

#include "TpmsTireData.h"

#include "sstream"
#include <iostream>

namespace src {

using namespace std;

void TpmsTireData::stateClean() {
	// TODO Auto-generated constructor stub
	this->state = MESSAGE_DATA_NOT_LOADED;
	this->trailerPosition = 0;
	this->tirePosition = 0;
	this->sensorID = 0;
	this->pressure = 0;
	this->temperature = 0;
	this->status.all = 0;
	this->numberOfTires = 0;
	this->tireData = false;
	this->repeaterBateryStatus = false;
	this->noTireData = false;
	this->updateConfirm = false;
	this->numberOfTires = false;
	this->nTires = false;
	this->dataError = false;
}

TpmsTireData::TpmsTireData() {
	// TODO Auto-generated constructor stub
	stateClean();
	for (uint8_t i = 0; i < 5; i++)
		batteryStatus[i] = 0;
}

TpmsTireData::TpmsTireData(TpmsRawData * rawData) {
	// TODO Auto-generated constructor stub
	stateClean();
	decompose(rawData);
	for (uint8_t i = 0; i < 5; i++)
		batteryStatus[i] = 0;
}

TpmsTireData::~TpmsTireData() {
	// TODO Auto-generated destructor stub
}

TireStatus TpmsTireData::getTireStatus(void) {
	return status;
}

uint8_t TpmsTireData::getIntTireStatus(void) {
	return status.all;
}

void TpmsTireData::decodeDataByte(std::vector<uint8_t>* data) {
	tirePosition = data->at(0) & 0B00011111;
	trailerPosition = (data->at(0) & 0B11100000) >> 5;
	sensorID = data->at(3);
	sensorID += data->at(2) << 8;
	sensorID += data->at(1) << 16;
	pressure = (data->at(4) << 8) + data->at(5);
	temperature = data->at(6) - 50;
	status.all = data->at(7);
	if (temperature > 100) {
		dataError = true;
		return;
	}
	if (pressure > 800) {
		dataError = true;
		return;
	}
	tireData = true;
}

int TpmsTireData::decompose(TpmsRawData * rawData) {
	stateClean();
	state = MESSAGE_DATA_OK;
	if (rawData->getFunctionNumber() == TIRE_DATA_TRANSMISSION) {
		int n = rawData->getSubFunction() & 0B00011111;
		if (n == 0) { //all data tires, general or in a trailer
			if (rawData->getData()->size() == 1) { //number of tires frame
				nTires = true;
				numberOfTires = (rawData->getData())->at(0);
			} else if (rawData->getData()->size() == 8) {
				std::vector<uint8_t> * data = rawData->getData();
				decodeDataByte(data);
			} else {
				state = MESSAGE_DECODE_FAIL;
				cout << "MESSAGE_DECODE_FAIL" << endl;
				return -1;
			}
		} else if (rawData->getData()->size() == 7) { //specific tire data
			std::vector<uint8_t> * data = rawData->getData();
			data->insert(data->begin(), rawData->getSubFunction());
			decodeDataByte(data);
		} else if (rawData->getFunctionNumber() == 0xFF) //no tire data available
			noTireData = true;
		else if (rawData->getFunctionNumber() == 0xAA) //confirmation
			updateConfirm = true;
		else
			state = MESSAGE_DECODE_FAIL;
	} else if (rawData->getFunctionNumber()
			== REPEATER_BATTERY_VOLTAGE_STATUS) {
		this->repeaterBateryStatus = true;
		for (uint8_t k = 0; k < rawData->getData()->size(); k++)
			batteryStatus[k] = (rawData->getData())->at(k);
	} else {
		state = MESSAGE_DECODE_FAIL;
		return -1;
	}
	return 0;
}

float TpmsTireData::getPressure(PRESSURE_UNIT unit) {
	if (state == MESSAGE_DATA_OK) {
		if (unit == BAR) {
			return ((float) pressure) * 0.025;
		} else if (unit == PSI)
			return ((float) pressure) * 0.362595;
		else
			return 0.0;
	} else
		return 0.0;
}
uint16_t TpmsTireData::getIntPressure(void) {
	return pressure;
}
int TpmsTireData::getTemperature(void) {
	if (state == MESSAGE_DATA_OK)
		return temperature;
	else
		return 0;
}

bool TpmsTireData::isTireData(void) {
	return tireData;
}
bool TpmsTireData::isNumberOfTires(void) {
	return nTires;
}
bool TpmsTireData::isUpdateConfirm(void) {
	return updateConfirm;
}
bool TpmsTireData::isNoTireData(void) {
	return noTireData;
}
bool src::TpmsTireData::isInvalidData(void) {
	return dataError;
}
bool TpmsTireData::isBaterryStatus(void) {
	return repeaterBateryStatus;
}

int TpmsTireData::getBaterryStatusAt(int trailer) {
	if (trailer < 5) {
		if (batteryStatus[trailer] == 0xFF)
			return 1;
		else
			return 0;
	}
	return 0;
}

int TpmsTireData::getNumberOfTires() const {
	return numberOfTires;
}

int TpmsTireData::getSensorId() const {
	return sensorID;
}

int TpmsTireData::getTirePosition() const {
	return tirePosition;
}

int TpmsTireData::getTrailerPosition() const {
	return trailerPosition;
}

string TpmsTireData::getStatusString(void) {
	stringstream ss;
	ss << (int) status.type.SENSOR_BATTERY_STATUS << ",";
	ss << (int) status.type.RECEIVING_OK << ",";
	ss << (int) status.type.HIGH_PRESSURE_ALARM << ",";
	ss << (int) status.type.LOW_PRESSURE_ALARM << ",";
	ss << (int) status.type.HIGH_TEMPERATURE << ",";
	ss << (int) status.type.FAST_LEAKAGE_ALERT << ",";
	ss << (int) status.type.SLOW_LEAKAGE_ALERT;
	return ss.str();
}

} /* namespace src */

