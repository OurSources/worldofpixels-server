#include "Logger.hpp"

#include <iostream>

Logger::LogLevel::LogLevel(std::string context, std::string levelName, std::ostream & out = std::cout)
: head("[" + context + "/" + levelName + "]: "),
  out(out),
  printHeader(true) { }

Logger::LogLevel & Logger::LogLevel::operator<<(endl_t endl) {
	printHeader = true;
	out << endl;
	return *this;
}

template <typename T>
Logger::LogLevel & Logger::LogLevel::operator<<(T const & msg) {
	if (printHeader) {
		printHeader = false;
		out << head << msg;
	} else {
		out << msg;
	}
	return *this;
}

Logger::Logger(std::string context)
: debug(context, "DEBG"),
  info(context, "INFO"),
  warn(context, "WARN"),
  error(context, "ERROR", std::cerr) { }

template <typename T>
Logger::LogLevel & Logger::operator<<(T const & msg) {
	info << msg;
	return info;
}
