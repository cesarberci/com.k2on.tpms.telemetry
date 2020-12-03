/*
 * TpmsData.cpp
 *
 *  Created on: 15 de ago de 2019
 *      Author: cesar
 */

#include "TpmsData.h"

namespace src {

TpmsData::TpmsData() {
	// TODO Auto-generated constructor stub

}

TpmsData::~TpmsData() {
	// TODO Auto-generated destructor stub
}

bool TpmsData::isTireData(void) {
	return false;
}
bool TpmsData::isNumberOfTires(void) {
	return false;
}
bool TpmsData::isUpdateConfirm(void) {
	return false;
}
bool TpmsData::isHandShake(void) {
	return false;
}
bool TpmsData::isNoTireData(void) {
	return false;
}
bool src::TpmsData::isInvalidData(void) {
	return false;
}

} /* namespace src */

bool src::TpmsData::isBaterryStatus(void) {
	return false;
}
