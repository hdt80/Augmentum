#ifndef LOGGER_H
#define LOGGER_H

#include <cstdarg>
#include <iostream>
#include <string>
#include <memory>

// Colors that can be used
namespace LogColor {
	extern char CLEAR[];
	extern char RESET[];
	extern char RED[];
	extern char GREEN[];
	extern char YELLOW[];
	extern char BLUE[];
	extern char MAGENTA[];
	extern char CYAN[];
	extern char WHITE[];
};

class Logger {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Nullary ctor
	Logger();

	// Dtor
	~Logger();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Print a log message to the output buffer
	//
	// tag - Tag used to identify the message
	// color - Color the tag is in. By passing a null no color is used.
	// func - Function the message is called from. By passing a null the
	//		function name is not printed. line must also be greater than zero
	// src - Source file the message is called from. By passing a null the
	//		source file is not printed
	// line - Line number the message is called from. By passing -1 the line
	//		number is not printed. func must also be non-null
	// fmt - How to format the string
	// ... - Args to populate the string with
	//
	void log(const std::string& tag, const char* color, const char* func,
		const char* src, unsigned int line, const std::string& fmt, ...);

	// Set the log file used by the Logger
	//
	// fileName - Name of the file to be used for logger. If the file does not
	//		exist it will be created. If fileName is empty stdout will be used
	//		for the log file (terminal)
	//
	void setLogFile(const std::string& fileName);

	// Set if the Logger will also output message to the screen, in addition
	//		to the output file
	//
	// b - To output to the screen as well
	//
	void setScreenOutput(bool b);

	// Flushes the output buffer
	//
	void flush();

	// Static methods //////////////////////////////////////////////////////////

	// Get the current instance of the Logger
	//
	// returns: The instance of the logger
	//
	static Logger& get() {
		static Logger instance;
		return instance;
	}

	// Get the date and time of the system
	//
	// returns: The date and time of the system formatted as YYYY:MM:DD HH:MM:SS
	//		The time is in UTC
	//
	static const std::string getDateTime();

	// Get the current time of the system
	//
	// returns: The time of the system formatted at HH:MM:SS. The time is in UTC
	//
	static const std::string getTime();

	// Get the name of the method from __PRETTY_FUNCTION__
	//
	// func - This should alway be __PRETTY_FUNCTION__
	//
	// returns: The method name from __PRETTY_FUNCTION__
	//
	static std::string methodName(const std::string& func,
		const std::string& pfunc);

private:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Copy ctor
	//
	Logger(const Logger&) = delete;

	// Operator overloads //////////////////////////////////////////////////////
	
	// Copy operator
	//
	Logger& operator=(const Logger&) = delete;
	
	// Vars ////////////////////////////////////////////////////////////////////
	
	// Output buffer used to print messages
	FILE* _output;
};

////////////////////////////////////////////////////////////////////////////////
// Logging config macros
////////////////////////////////////////////////////////////////////////////////

#include "Logger_Config.h"

#define __NICE_FUNC__ Logger::methodName(__func__, __PRETTY_FUNCTION__).c_str()

// Should the function the CORE_* is called from be used?
#ifdef LOGGER_USE_FUNCTION

	// Use a nicer looking function macro in g++, unless the LOGGER_SIMPLE macro
	// has been defined
	#if (defined(__GNUC__) || defined(__GNUG__)) && !defined(LOGGER_SIMPLE)
		#define LOG_FUNC __NICE_FUNC__
	#else
		#define LOG_FUNC __FUNCTION__
	#endif // __GNUC__ || __GNUG__ && !LOGGER_SIMPLE

#else
	#define LOG_FUNC nullptr
#endif // LOGGER_USE_FUNCTION

// Should the line number the CORE_* is called from be used?
#ifdef LOGGER_USE_LINE
	#define LOG_LINE __LINE__
#else
	#define LOG_LINE -1
#endif // LOGGER_USE_LINE

// Should the file containing the CORE_* is called from be used?
#ifdef LOGGER_USE_FILE
	#define LOG_FILE __FILE__
#else
	#define LOG_FILE nullptr
#endif // LOGGER_USE_FILE

////////////////////////////////////////////////////////////////////////////////
// Logging macros
////////////////////////////////////////////////////////////////////////////////

// Simple ones that don't include function name and all that good stuff

#define SDEBUG(...) \
	Logger::get().log("DBUG", LOGGER_COLOR_DEBUG, nullptr, nullptr, \
		-1, __VA_ARGS__)

#define SINFO(...) \
	Logger::get().log("INFO", LOGGER_COLOR_INFO, nullptr, nullptr, \
		-1, __VA_ARGS__)

#define SWARN(...) \
	Logger::get().log("WARN", LOGGER_COLOR_WARN, nullptr, nullptr, \
		-1, __VA_ARGS__)

#define SERROR(...) \
	Logger::get().log("ERRO", LOGGER_COLOR_ERROR, nullptr, nullptr, \
		-1, __VA_ARGS__)

#define SFATAL(...) \
	do { \
		Logger::get().log("FATL", LOGGER_COLOR_FATAL, nullptr, nullptr, \
			-1, __VA_ARGS__); \
		std::terminate(); \
	while (0)

#define SLOG(tag, ...) \
	Logger::get().log(tag, LOGGER_COLOR_INFO, nullptr, nullptr, \
		-1, __VA_ARGS__)

// Complete logging macros, with functions and good stuff

#define AG_DEBUG(...) \
	Logger::get().log("DBUG", LOGGER_COLOR_DEBUG, LOG_FUNC, LOG_FILE, \
		LOG_LINE, __VA_ARGS__)

#define AG_INFO(...) \
	Logger::get().log("INFO", LOGGER_COLOR_INFO, LOG_FUNC, LOG_FILE, \
		LOG_LINE, __VA_ARGS__)

#define AG_WARN(...) \
	Logger::get().log("WARN", LOGGER_COLOR_WARN, LOG_FUNC, LOG_FILE, \
		LOG_LINE, __VA_ARGS__)

#define AG_ERROR(...) \
	Logger::get().log("ERRO", LOGGER_COLOR_ERROR, LOG_FUNC, LOG_FILE, \
		LOG_LINE, __VA_ARGS__)

#define AG_FATAL(...) \
	do { \
		Logger::get().log("FATL", LOGGER_COLOR_FATAL, LOG_FUNC, LOG_FILE, \
			LOG_LINE, __VAR_ARGS__); \
		std::terminate(); \
	while (0)

#define AG_LOG(tag, ...) \
	Logger::get().log(tag, LOGGER_COLOR_LOG, LOG_FUNC, LOG_FILE, \
		LOG_LINE, __VA_ARGS__)

#endif // LOGGER_H
