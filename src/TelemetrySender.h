// TelemetrySender.h
#ifndef TELEMETRYSENDER_H
#define TELEMETRYSENDER_H

#include <string>
#include <functional>

namespace src {

class TelemetrySender {
public:
	using Callback = std::function<void(int, std::string)>;
	void send(std::string topic, std::string message, Callback callback);
};

}  // namespace src

#endif  // TELEMETRYSENDER_H
