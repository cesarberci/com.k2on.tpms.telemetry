// TelemetrySender.cpp
#include "TelemetrySender.h"
#include <sstream>
#include <iostream>
#include <thread>
#include <cstdlib>

namespace src {

void TelemetrySender::send(std::string topic, std::string message, Callback callback) {
    std::thread([=]() {
        std::ostringstream oss;
        oss << "telemetry_send " << topic << " '" << message << "'";
        int result = system(oss.str().c_str());

        // Execute callback function
        callback(result, message);
    }).detach();
}

}  // namespace src
