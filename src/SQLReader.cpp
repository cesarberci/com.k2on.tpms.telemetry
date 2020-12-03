/*
 * SQLReader.cpp
 *
 *  Created on: 28 de fev de 2020
 *      Author: cesar
 */

#include "SQLReader.h"

#include "utils.h"

#include <iostream>
#include <curl/curl.h>
#include <string.h>

namespace src {

using namespace std;

SQLReader* SQLReader::instance = 0;
string readBuffer;

void (*callback)(void);

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
		void *userp);

SQLReader::SQLReader() {
	// TODO Auto-generated constructor stub
}

SQLReader* SQLReader::getInstance(void) {
	if (instance == 0)
		instance = new SQLReader();
	return instance;
}

SQLReader::~SQLReader() {
	// TODO Auto-generated destructor stub
	instance = 0;
	readBuffer.clear();
	readBuffer.shrink_to_fit();
}

void SQLReader::sendRequest(stringstream * request, void * callback) {
	curl_global_cleanup();
	CURL* curl;
	CURLcode res;
	readBuffer.clear();
	readBuffer.shrink_to_fit();
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, request->str().c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	res = curl_easy_perform(curl);
	/* Check for errors */
	if (res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
	curl_easy_cleanup(curl);
	cout << request->str() << endl;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
		void *userp) {
	((std::string*) userp)->append((char*) contents, size * nmemb);
	cout << "Response: " << readBuffer << endl;
	__run(callback);
	return size * nmemb;
}

} /* namespace src */
