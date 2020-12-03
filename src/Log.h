/*
 * Log.h
 *
 *  Created on: 17 de ago de 2019
 *      Author: cesar
 */

#ifndef LOG_H_
#define LOG_H_

// Include from Include stereotype (header)
#include "Pkg_src.h"
// End of Include stereotype (header)

#include <string.h>
#include <sstream>

#include "TpmsTireData.h"

namespace src {

class Log {
public:
	Log();
	Log(TpmsTireData * tireData);
	virtual ~Log();
private:
	std::string getTimeStamp(void);
	/**
	 * \brief Get disk space available
	 * \details
	 * This function is used to get the all amount of space available in disk.
	 * \return space Float number between 0.0% and 100.0%, representing the available space
	 * related to total disk space.
	 */
	float getSpaceAvailable(void);
	void logRecycle(std::string run);
	void saveFile(std::ofstream file, TpmsTireData* tireData);
};

} /* namespace src */

#endif /* LOG_H_ */
