/*
 * TPMSMessage.cpp
 *
 *  Created on: 6 de ago de 2019
 *      Author: cesar
 */

#include "TpmsRawData.h"

#include "iostream"

namespace src {

using namespace std;


TpmsRawData::TpmsRawData() { // @suppress("Class members should be properly initialized")
	reset();
}

TpmsRawData::~TpmsRawData() {
	// TODO Auto-generated destructor stub
}

int TpmsRawData::addByte(uint8_t b) {
	switch (state) {
	case CLEAR_START:
		if (b == START_BYTE) {
			start = b;
			verifyByte = 0;
			state++;
		} else {
			errorn |= INVALID_START_BYTE;
			return -1;
		}
		break;
	case HEAD_OBJECT:
		object = b;
		state++;
		if (b != TPMS_HOST)
			errorn |= INCORRECT_ADDR;
		break;
	case HEAD_ORIGINAL_ADDR:
		originalAddress = b;
		state++;
		break;
	case HEAD_LEN:
		length = b;
		state++;
		receiveCounter = b - 5;
		if (receiveCounter > 70)
			errorn |= INVALID_LEN;
		break;
	case DATA_FUNCTION:
		functionNumber = b;
		receiveCounter--;
		if (receiveCounter == 0)
			state = VERIFY;
		else
			state++;
		if (!validFunctionNumber())
			errorn |= INVALID_FUNCTION_NUMBER;
		break;
	case DATA_SUBFUNCTION:
		subFunctionNumber = b;
		if (!validSubFunctionNumber())
			errorn |= INVALID_SUBFUNCTION_NUMBER;
		receiveCounter--;
		if (receiveCounter == 0)
			state = VERIFY;
		else
			state++;
		break;
	case DATA_DATA:
		data.push_back(b);
		receiveCounter--;
		if (receiveCounter == 0)
			state++;
		break;
	case VERIFY:
		if (verifyByte == b)
			state = MESSAGE_COMPLETE;
		else {
			state = VERIFICATION_ERROR;
			errorn |= VERIFY_FAIL;
			cout<<"verify error"<<endl;
		}
		return 0;
	}
	if (state > VERIFICATION_ERROR) {
		errorn = INVALID_NEW_BYTE;
		return -1;
	}
	if (errorn != TPMS_MSG_OK) {
		msg_start <<= 8;
		msg_start += b;
		if ((msg_start & 0x00FFFFFF) == 0xAAA141) {
			reset();
			state = HEAD_LEN;
			start = 0xAA;
			object = 0xA1;
			originalAddress = 0x41;
			verifyByte = 0x4B;
		}
	}
	verifyByte += b;
	return 0;
}

int TpmsRawData::getState(void) {
	return state;
}

int TpmsRawData::getErrorCode(void) {
	return errorn;
}

bool TpmsRawData::isComplete(void) {
	if (state == MESSAGE_COMPLETE)
		return true;
	else
		return false;
}

bool TpmsRawData::validFunctionNumber() {
	return true;
}
bool TpmsRawData::validSubFunctionNumber() {
	return true;
}

uint8_t TpmsRawData::getFunctionNumber(void) {
	if (state == MESSAGE_COMPLETE)
		return functionNumber;
	else
		return -1;
}
uint8_t TpmsRawData::getLen(void) {
	if (state == MESSAGE_COMPLETE)
		return length;
	else
		return 0;

}
std::vector<uint8_t>* TpmsRawData::getData(void) {
	if (state == MESSAGE_COMPLETE)
		return &data;
	else
		return 0;
}

uint8_t TpmsRawData::getSubFunction(void) {
	if (state == MESSAGE_COMPLETE)
		return subFunctionNumber;
	else
		return 0;
}

void TpmsRawData::reset(void) {
	msg_start = 0;
	state = CLEAR_START;
	data.clear();
	verifyByte = 0;
	start = 0;
	object = 0;
	originalAddress = 0;
	length = 0;
	functionNumber = 0;
	subFunctionNumber = 0;
	receiveCounter = 0;
	errorn = TPMS_MSG_OK;
}

} /* namespace src */

