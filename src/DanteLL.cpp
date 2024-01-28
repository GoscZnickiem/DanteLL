#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>

#include "DanteLL.hpp"

namespace DLog {

//==================================================================================
//		Logger Class
//==================================================================================

Logger::Logger()
	:m_level(Level::ENTRY) {}

void Logger::log(const std::string& message) {
log(Level::ENTRY, message);
}

void Logger::log(Level logLevel, const std::string& message) {
	std::lock_guard<std::mutex> lock(m_mutex);

	if(logLevel >= m_level) {
		std::cout << "[" << getLevelName(logLevel) << "] (" << getCurrentTimestamp() << ") " << message << "\n";
	}
}

void Logger::setLogLevel(Level level) {
	m_level = level;
}

std::string Logger::getLevelName(Level level) {
	switch (level) {
		case ENTRY: return "  ENTRY  ";
		case DEBUG: return "  DEBUG  ";
		case INFO: return "   INF   ";
		case WARNING: return " WARNING ";
		case ERROR: return "  ERROR  ";
		case FATAL: return "  FATAL  ";
		default: return "__UNKNOWN__";
	}
}

std::string Logger::getCurrentTimestamp() {
	std::time_t now = std::time(nullptr);
	std::tm* local = std::localtime(&now);

	std::stringstream stream;
	stream << std::put_time(local, "%d-%m-%Y %H:%M:%S");
	return stream.str();
}


}
