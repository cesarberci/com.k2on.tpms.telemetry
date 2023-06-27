/*
 * BDDataExanger.h
 *
 *  Created on: 6 de dez de 2021
 *      Author: cesar
 */

#ifndef DBDATAEXANGER_H_
#define DBDATAEXANGER_H_

#include <mariadb/mysql.h>
#include <string>
#include <map>

class DBDataExanger {
public:
	virtual ~DBDataExanger();
	void selectDB(std::string db);
	std::string getQueryResult(std::string query);
	void sendQuery(std::string query);
	static DBDataExanger * getInstance();
	std::map<std::string, std::string> getLogById(int id);
	std::string getDeviceId();
	int getMaxId();
private:
	DBDataExanger();
	MYSQL *con;
	static DBDataExanger * instance;
};

#endif /* DBDATAEXANGER_H_ */
