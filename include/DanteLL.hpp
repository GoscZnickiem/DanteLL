// The main header file of this project

#ifndef GZN_DANTELL_H
#define GZN_DANTELL_H

#include <string>


namespace DLog {


class Logger {
public:
	Logger();

	void log(const std::string&);

private:
	uint64_t logCount;
};

void test();


}




#endif // !GZN_DANTELL_H
