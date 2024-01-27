#include "DanteLL.hpp"

int main () {

	DLog::test();

	DLog::Logger logger;
	logger.log("Hello from logger class!");
	logger.log("Second message");
	logger.log("Now this message has endline\n");
	logger.log("And this message does not");

	return 0;
}
