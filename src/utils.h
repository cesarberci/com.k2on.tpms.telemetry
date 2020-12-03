/*
 * utils.h
 *
 *  Created on: 22 de jun de 2019
 *      Author: cesar
 */

#ifndef SRC_GEN_MODBUSMANAGER_UTILS_UTILS_H_
#define SRC_GEN_MODBUSMANAGER_UTILS_UTILS_H_

#include <chrono>
#include <thread>

using namespace std::chrono;

#define null_delete(x) {delete x; x = NULL;}


#define sleep_ms(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
#define currentTimeMillis() duration_cast< milliseconds >(system_clock::now().time_since_epoch());

void __run(void (*function)(void));

#endif /* SRC_GEN_MODBUSMANAGER_UTILS_UTILS_H_ */
