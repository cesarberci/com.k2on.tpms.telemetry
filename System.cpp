//============================================================================
// Name        : tpms.cpp
// Author      : Cesar Daltoe Berci
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "System.h"

#include <iostream>

#include "src/TpmsDevice.h"
#include "src/Communication.h"
#include "src/TpmsDefinitions.h"
#include "src/DigitalIO.h"

#include <iostream>
#include <unistd.h>
#include<iostream>
#include <sstream>

using namespace std;
using namespace src;

void showContent(void) {
	cout << "****   TPMS DATALOGGER  ****" << endl;
	cout << "Copyright: K2On" << endl;
	cout << "Author: Cesar Daltoe Berci" << endl;
	cout << "Version: ";
	cout << completeVersion << endl << endl << endl;
	cout << "This software should be used to read" << endl;
	cout << "TPMS device and generates log files on" << endl;
	cout << "every new data input" << endl;
	cout << "All stored data will be available for" << endl;
	cout << "the user in the /var/log/tpms/ directory." << endl;
	cout << "\n\n\nUsage:" << endl;
	cout << "com.K2On.tpms DEVICE" << endl;
	exit(0);
}

int main(int argc, char*argv[]) {
	if (argc == 1)
		showContent();
	TpmsDevice dev;
	Communication * comm = Communication::getInstance();
	comm->setDev(argv[1]);
	comm->add(&dev);
	comm->start();
	sleep(1);
	while (true) {
		comm->writeStr(&REQUEST_ALL_TIRES_DATA[0],
				sizeof REQUEST_ALL_TIRES_DATA);
		//sleep(3600);
		sleep(2);
	}

	return 0;
}

