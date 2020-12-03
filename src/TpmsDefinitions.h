/*
 * TpmsDefinitions.h
 *
 *  Created on: 15 de ago de 2019
 *      Author: cesar
 */

#ifndef TPMSDEFINITIONS_H_
#define TPMSDEFINITIONS_H_

const unsigned char HANDSHAKE[] = {0xAA, 0x41, 0xA1, 0x06, 0x11, 0xA3};
const unsigned char REQUEST_ALL_TIRES_DATA[] = {0xAA, 0x41, 0xA1, 0x07, 0x63, 0x00, 0xF6};


#endif /* TPMSDEFINITIONS_H_ */
