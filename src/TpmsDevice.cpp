/*
 * TpmsDevice.cpp
 *
 *  Created on: 17 de ago de 2019
 *      Author: cesar
 */

#include <iostream>

#include "TpmsDevice.h"
#include "TpmsData.h"
#include "TpmsTireData.h"
#include "Log.h"
#include <stdexcept>
#include <thread>

namespace src {

using namespace std;

TpmsDevice::TpmsDevice() {
	comm = Communication::getInstance();
	rawMsg = new TpmsRawData();
}

TpmsDevice::~TpmsDevice() {
	delete rawMsg;
}

} /* namespace src */

void src::TpmsDevice::update() {
	unsigned char b = comm->getByte();
	rawMsg->addByte(b);
	if (rawMsg->isComplete()) { //message complete handler
		if (rawMsg->getFunctionNumber() == HANDSHAKE_SIGNAL) {
			//not implemented!
		} else if (rawMsg->getFunctionNumber()
				== ALERT_PARAMETERS_TRANSMISSION) {
			//not implemented!
		} else if (rawMsg->getFunctionNumber() == TIRE_DATA_TRANSMISSION) {
			//thread t(_tire_data,rawMsg);
			Log lg(new TpmsTireData(rawMsg));
		} else if (rawMsg->getFunctionNumber() == SEND_TRAILER_ID) {
			//not implemented!
		} else if (rawMsg->getFunctionNumber() == DELETE_CODED_SENSOR_ID) {
			//not implemented!
		} else if (rawMsg->getFunctionNumber() == TPMS_SENSORS_ID_LEARNING) {
			//not implemented!
		} else if (rawMsg->getFunctionNumber()
				== FMS_REQUEST_TPMS_MODULE_TO_SEND_THE_TRAILER_DATA_TO_REPEATER) {
			//not implemented!
		} else if (rawMsg->getFunctionNumber()
				== REPEATER_BATTERY_VOLTAGE_STATUS) {
			//not implemented!
		} else
			throw std::invalid_argument(
					"TPMS Prototcol: Invalid function Number!");
		rawMsg->reset();
	}
}
