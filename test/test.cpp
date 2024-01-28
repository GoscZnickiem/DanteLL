#include "DanteLL.hpp"

int main () {

	DLog::Logger logger;
	logger.log("Hello from logger class!");
	logger.log("Second message");
	logger.log("Now this message has endline\n");
	logger.log("And this message does not");
	logger.log(DLog::ENTRY, "entry");
	logger.log(DLog::DEBUG, "debug");
	logger.log(DLog::INFO, "info");
	logger.log(DLog::WARNING, "warning");
	logger.log(DLog::ERROR, "error");
	logger.log(DLog::FATAL, "fatal");

	logger.log("\nchange level to: INFO\n");
	logger.setLogLevel(DLog::INFO);

	logger.log(DLog::ENTRY, "entry");
	logger.log(DLog::DEBUG, "debug");
	logger.log(DLog::INFO, "info");
	logger.log(DLog::WARNING, "warning");
	logger.log(DLog::ERROR, "error");
	logger.log(DLog::FATAL, "fatal");

	return 0;
}
