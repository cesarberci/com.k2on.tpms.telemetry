/*
 * TPMSMessage.h
 *
 *  Created on: 6 de ago de 2019
 *      Author: cesar
 *
 *      TPMS raw data acquisition and control
 */

#ifndef TPMSRAWDATA_H_
#define TPMSRAWDATA_H_

// Include from Include stereotype (header)
#include "Pkg_src.h"
// End of Include stereotype (header)

#include "stdint.h"
#include <vector>

namespace src {

#define START_BYTE 0xAA
#define TPMS_HOST 0xA1

enum _message_state {
	CLEAR_START,
	HEAD_OBJECT,
	HEAD_ORIGINAL_ADDR,
	HEAD_LEN,
	DATA_FUNCTION,
	DATA_SUBFUNCTION,
	DATA_DATA,
	VERIFY,
	MESSAGE_COMPLETE,
	VERIFICATION_ERROR
};

enum _message_errorn {
	TPMS_MSG_OK = 0,
	INVALID_START_BYTE = 1,
	INVALID_LEN = 2,
	INVALID_FUNCTION_NUMBER = 4,
	INVALID_SUBFUNCTION_NUMBER = 8,
	VERIFY_FAIL = 16,
	INCORRECT_ADDR = 32,
	INVALID_NEW_BYTE = 64,
};

class TpmsRawData {
public:
	TpmsRawData();
	virtual ~TpmsRawData();
	int addByte(uint8_t b);
	int getState(void);
	int getErrorCode(void);
	bool isComplete(void);
	uint8_t getFunctionNumber(void);
	uint8_t getLen(void);
	uint8_t getSubFunction(void);
	std::vector<uint8_t>* getData(void);
	void reset(void);
private:
	bool validFunctionNumber();
	bool validSubFunctionNumber();
	uint8_t start;
	uint8_t object;
	uint8_t originalAddress;
	uint8_t length;
	uint8_t functionNumber;
	uint8_t subFunctionNumber;
	uint8_t verifyByte;
	std::vector<uint8_t> data;
	int state;
	uint8_t receiveCounter;
	uint8_t errorn;
	unsigned long msg_start;
};

} /* namespace src */

#endif /* TPMSRAWDATA_H_ */
