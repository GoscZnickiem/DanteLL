#include <iostream>

#include "DanteLL.hpp"

namespace DLog {

//==================================================================================
//		Logger Class
//==================================================================================

Logger::Logger()
	:logCount(0) {

	std::cout << "Logger created\n";
}

void Logger::log(const std::string& msg) {
	std::string end;
	if(msg.find("\n", msg.length() - 1) == std::string::npos) {
		end = "\n";
	}
	logCount++;
	std::cout << " [" << logCount << "] " << msg << end;
}

//==================================================================================
//		Nothing important really
//==================================================================================

void test() {
	std::cout << "Hello world!\n";
}




}
