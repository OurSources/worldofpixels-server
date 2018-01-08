#pragma once

#include <string>

class Logger {
public:
	class LogLevel {
		using endl_t = std::ostream & (std::ostream&); // ??
		std::string const head;
		std::ostream & out;
		bool printHeader;

	public:
		LogLevel(std::string context, std::string levelName, std::ostream &);

		LogLevel & operator<<(endl_t);

		template <typename T>
		LogLevel & operator<<(T const &);
	};

	LogLevel debug;
	LogLevel info;
	LogLevel warn;
	LogLevel error;

	Logger(std::string context);

	template <typename T>
	LogLevel & operator<<(T const &); /* Defaults to info */
};
