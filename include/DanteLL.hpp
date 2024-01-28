// The main header file of this project

#ifndef GZN_DANTELL_HPP
#define GZN_DANTELL_HPP

#include <mutex>
#include <string>


namespace DLog {


enum Level {
	ENTRY = 0,
	DEBUG = 1,
	INFO = 2,
	WARNING = 3,
	ERROR = 4,
	FATAL = 5
};

class Logger {
public:
	Logger();
	explicit Logger(Level);

	void log(const std::string&);
	void log(Level, const std::string&);

	void setLogLevel(Level);

private:
	std::mutex m_mutex;
	Level m_level;

	[[nodiscard]] static std::string getLevelName(Level);
	[[nodiscard]] static std::string getCurrentTimestamp();

};


}




#endif // !GZN_DANTELL_HPP
