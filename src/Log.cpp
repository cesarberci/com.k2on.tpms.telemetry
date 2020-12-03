/*
 * Log.cpp
 *
 *  Created on: 17 de ago de 2019
 *      Author: cesar
 */

#include "Log.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <time.h>
#include <iostream>
#include <exception>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/statvfs.h>

#include "utils.h"
#include "SQLReader.h"

namespace src {

using namespace std;

Log::Log() {
	// TODO Auto-generated constructor stub

}

Log::~Log() {
	// TODO Auto-generated destructor stub

}

void src::Log::logRecycle(string run) {
	if (getSpaceAvailable() < 40.0) {
		system(run.c_str()); //delete the oldest file using log_control.sh
	}
}

src::Log::Log(TpmsTireData* tireData) {
	if (tireData->isTireData()) {
		stringstream ss;
		ss
				<< "http://127.0.0.1/database/dbInterface.php?sql=INSERT%20INTO%20Log(TrailerPosition,TireID,SensorID,Temperature,Pressure,StatusByte)%20VALUES(";
		ss << tireData->getTrailerPosition() << ",";
		ss << tireData->getTirePosition() << ",";
		ss << tireData->getSensorId() << ",";
		ss << tireData->getTemperature() << ",";
		ss << tireData->getIntPressure() << ",";
		ss << (int) tireData->getIntTireStatus() << ");";
		SQLReader::getInstance()->sendRequest(&ss, 0);
	} else if (tireData->isNumberOfTires()) {
		stringstream ss;
		ss
				<< "http://127.0.0.1/database/dbInterface.php?sql=UPDATE%20Device%20SET%20Tires%20=%20";
		ss << tireData->getNumberOfTires();
		ss << "%20WHERE%20ID%20=%201;";
		SQLReader::getInstance()->sendRequest(&ss, 0);
	} else if (tireData->isInvalidData()) {
		stringstream ss;
		ss
				<< "http://127.0.0.1/database/dbInterface.php?sql=INSERT%20INTO%20ErrorLog(ErrorCode,TrailerPosition,Tire)%20VALUES(1,";
		ss << tireData->getTrailerPosition() << ",";
		ss << tireData->getTirePosition() << ");";
		SQLReader::getInstance()->sendRequest(&ss, 0);
	} else if (tireData->isBaterryStatus()) {
		stringstream ss;
		ss
				<< "http://127.0.0.1/database/dbInterface.php?sql=UPDATE%20Device%20SET%20";
		ss << "TraktorBattery%20=%20" << tireData->getBaterryStatusAt(0)
				<< ",%20";
		ss << "Trailer1Battery%20=%20" << tireData->getBaterryStatusAt(1)
				<< ",%20";
		ss << "Trailer2Battery%20=%20" << tireData->getBaterryStatusAt(2)
				<< ",%20";
		ss << "Trailer3Battery%20=%20" << tireData->getBaterryStatusAt(3)
				<< ",%20";
		ss << "Trailer4Battery%20=%20" << tireData->getBaterryStatusAt(4);
		ss << "%20WHERE%20ID%20=%201;";
		SQLReader::getInstance()->sendRequest(&ss, 0);
	}
	delete tireData;
}

string Log::getTimeStamp(void) {
	time_t timer;
	time(&timer);
	struct tm * timeinfo;
	timeinfo = localtime(&timer);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%d-%m-%Y_%Ih%Mm%Ss", timeinfo);
	string dateStr(buffer);
	return dateStr;
}

float Log::getSpaceAvailable(void) {
	struct statvfs buffer;
	int ret = statvfs("/", &buffer);
	float av_per = 0;
	if (!ret) {
		long long fs_size = (long long) buffer.f_frsize
				* (long long) buffer.f_blocks;
		long long av_size = (long long) buffer.f_frsize
				* (long long) buffer.f_bavail;
		av_per = ((float) av_size / (float) fs_size) * 100;
		return av_per;
	} else
		return -1;
}

} /* namespace src */
