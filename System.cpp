//============================================================================
// Name        : tpms.cpp
// Author      : Cesar Daltoe Berci
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "System.h"

#include <iostream>

#include <iostream>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <queue>
#include <mutex>

#include "src/DBDataExanger.h"
#include "src/TelemetrySender.h"

using namespace std;
using namespace src;

std::queue<std::string> messageStack;
mutex mtx;

void showContent(void) {
	cout << "****   TPMS TELEMETRY  ****" << endl;
	cout << "Copyright: K2On" << endl;
	cout << "Author: Cesar Daltoe Berci" << endl;
	cout << "Version: ";
	cout << completeVersion << endl << endl << endl;
	exit(0);
}

void tpms_callback(int result, std::string message) {
	if (result != 0) {
		lock_guard<mutex> lock(mtx);
		messageStack.push(message);
	}
}

int main(int argc, char *argv[]) {
	if (argc == 2)
		showContent();

	DBDataExanger *db = DBDataExanger::getInstance();
	db->selectDB("TPMS");

	TelemetrySender sender;

	int maxId = db->getMaxId();  // Get the current max ID

	while (true) {
		sleep(1);  // Wait for 1 second

		int newMaxId = db->getMaxId();  // Get the new max ID

		if (newMaxId > maxId) {  // If there's a new record
			//std::cout << "New record detected. ID: " << newMaxId << std::endl;
			maxId = newMaxId;  // Update the max ID

						std::map<std::string, std::string> logData = db->getLogById(maxId);
						std::string deviceId = db->getDeviceId();

						std::stringstream ss;
						ss << "{\"Device\": \"" << deviceId << "\", \"TrailerPosition\": "
								<< logData["TrailerPosition"] << ", \"Tire\": "
								<< logData["TireID"] << ", \"Temperature\": "
								<< logData["Temperature"] << ", \"Pressure\": "
								<< logData["Pressure"] << ", \"StatusByte\": "
								<< logData["StatusByte"] << ", \"TimeStamp\" : \""
								<< logData["TimeStamp"] << "\"}";

						std::string jsonMessage = ss.str();
						//std::cout << "JSON Message: " << jsonMessage << std::endl;
						sender.send("tpms", jsonMessage, tpms_callback);
		}

		if (!messageStack.empty()) {
			lock_guard<mutex> lock(mtx);
			std::string message = messageStack.front();
			messageStack.pop();
			sender.send("tpms", message, tpms_callback);
		}
	}
	return 0;
}

