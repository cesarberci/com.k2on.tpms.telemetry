/*
 * BDDataExanger.cpp
 *
 *  Created on: 6 de dez de 2021
 *      Author: cesar
 */
#include "DBDataExanger.h"

#include <stdio.h>
#include <stdlib.h>
#include <sstream>

DBDataExanger *DBDataExanger::instance = 0;

void finish_with_error(MYSQL *con) {
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

void DBDataExanger::sendQuery(std::string query) {
	if (mysql_query(con, query.c_str()))
		finish_with_error(con);
}

DBDataExanger::DBDataExanger() {
	// TODO Auto-generated constructor stub
	con = mysql_init(NULL);
	if (mysql_real_connect(con, "localhost", "root", "k2on2020",
	NULL, 0, NULL, 0) == NULL)
		finish_with_error(con);

}

DBDataExanger::~DBDataExanger() {
	// TODO Auto-generated destructor stub
}

void DBDataExanger::selectDB(std::string db) {
	if (mysql_query(con, ("USE " + db).c_str()))
		finish_with_error(con);
}

std::string DBDataExanger::getQueryResult(std::string query) {
	if (mysql_query(con, query.c_str()))
		finish_with_error(con);
	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL)
		finish_with_error(con);
	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	std::stringstream ss;
	while ((row = mysql_fetch_row(result))) {
		for (int i = 0; i < num_fields; i++)
			ss << row[i] << "\n";
		//printf("%s ", row[i] ? row[i] : "NULL");
	}
	return ss.str();
}

DBDataExanger* DBDataExanger::getInstance() {
	if (instance == 0) {
		instance = new DBDataExanger();
	}
	return instance;
}

int DBDataExanger::getMaxId() {
    std::string queryResult = getQueryResult("SELECT MAX(ID) as maxID FROM Log;");
    return std::stoi(queryResult);
}


std::map<std::string, std::string> DBDataExanger::getLogById(int id) {
    std::string queryResult = getQueryResult("SELECT * FROM Log WHERE ID=" + std::to_string(id) + ";");

    std::map<std::string, std::string> logData;
    std::istringstream ss(queryResult);
    std::string token;

    std::getline(ss, token, '\n');  // ID
    logData["ID"] = token;

    std::getline(ss, token, '\n');  // TimeStamp
    logData["TimeStamp"] = token;

    std::getline(ss, token, '\n');  // TrailerPosition
    logData["TrailerPosition"] = token;

    std::getline(ss, token, '\n');  // TireID
    logData["TireID"] = token;

    std::getline(ss, token, '\n');  // SensorID
    logData["SensorID"] = token;

    std::getline(ss, token, '\n');  // Temperature
    logData["Temperature"] = token;

    std::getline(ss, token, '\n');  // Pressure
    logData["Pressure"] = token;

    std::getline(ss, token, '\n');  // StatusByte
    logData["StatusByte"] = token;

    return logData;
}


std::string DBDataExanger::getDeviceId() {
    std::string queryResult = getQueryResult("SELECT DeviceID FROM Config LIMIT 1;");

    return queryResult.substr(0, queryResult.size() - 1);  // Remove a nova linha do final
}

