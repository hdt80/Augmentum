#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <stdio.h>

#include "Colors.h"
#include "trmclr.hpp"

//namespace {
//	static void CORE_INFO(const char* fmt, ...);
//	static void CORE_WARNING(const char* fmt, ...);
//	static void CORE_WARN(const char* fmt, ...);
//	static void CORE_ERROR(const char* fmt, ...);
//}


class Logger {
public:
	static Logger& instance() {
		static Logger instance;
		return instance;
	}

	~Logger();

	static const std::string CurrentDateTime();
	static const std::string CurrentTime();

	static trmclr::Style grey;
	static trmclr::Style yellow;
	static trmclr::Style orange;
	static trmclr::Style red;

	void setLogFile(const char* filename, bool isPlainText = false, bool showOnScreen = false);

	void log(const std::string& tag, const char* funcName, const char* sourceFile,
	         unsigned int lineNum, const std::string& fmt, ...);

	// Flushes output buffer. Used for critical calls
	void flush();

protected:
	Logger();

private:
	Logger(const Logger&);
	Logger& operator=(const Logger&);

	void fillOutputBuffer(std::string& outputBuffer,
	                      const std::string& tag, const std::string& msg,
	                      const char* funcName, const char* sourceFile, unsigned int lineNum);
	void fillFileBuffer(std::string& outputBuffer,
	                    const std::string& tag, const std::string& msg,
	                    const char* funcName, const char* sourceFile, unsigned int lineNum);

	inline FILE* loadFileStream(FILE* stream, const char* filename);

	FILE* m_pLogFile;
	bool isHTML = false;
	bool printToScreen = false;
}; /* Logger */

#ifndef NDEBUG // If in debug mode define debugger break symbols for SIGTRAP
#ifdef __unix__ // Linux & BSD
    #include <signal.h>
    #define DEBUG_BREAK raise(SIGTRAP)
#elif defined(_MSC_VER) // Visual studio 
    #define DEBUG_BREAK __debugbreak();
#elif defined(__GNUG__) // GNU C Compiler
    #define DEBUG_BREAK __debugbreak(); // This one works fine
#else
    #warning "Unknown Operating System, debug break support will not be included"
    #define DEBUG_BREAK 0 // Remove debug break support on other platforms
#endif

// do-while removes the ; at the end of the call
#define CORE_ASSERT(expr) \
	do {\
		if(!(expr)) {\
			Logger::instance().log("ASSERT", __FUNCTION__, __FILE__, __LINE__, #expr); \
			Logger::instance().flush(); \
            DEBUG_BREAK; \
		} \
	} \
	while(0)\

#define CORE_FATAL(...) \
    do {\
        Logger::instance().log("FATAL", __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);\
        Logger::instance().flush(); \
        DEBUG_BREAK; \
        std::terminate(); \
    } \
    while(0)\

#define CORE_ERROR(...) \
    do {\
        Logger::instance().log("ERROR", __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); \
        Logger::instance().flush(); \
    } \
    while(0)\

#define CORE_WARNING(...) \
    do {\
        Logger::instance().log(";[033m0};WARNING", __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);\
        Logger::instance().flush(); \
    } \
    while(0)\

#define CORE_WARN(...) \
    do {\
        Logger::instance().log(";[033m0};WARNING", __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);\
        Logger::instance().flush(); \
    } \
    while(0)\

#define CORE_DEBUG(...) \
    do {\
        Logger::instance().log("DEBUG", __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); \
        Logger::instance().flush(); \
    } \
    while(0) \

#define CORE_LOG(tag, ...) \
    do {\
        Logger::instance().log(tag, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); \
        Logger::instance().flush(); \
    } \
    while(0) \

#define CORE_VERBOSE(...) \
    do {\
        Logger::instance().log("VERBOSE", __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); \
    } \
    while(0) \

#else // Not in debug mode

// Keep errors and warnings, just exclude func, file and line info
#define CORE_FATAL(...) \
    do {\
        Logger::instance().log("FATAL", NULL, NULL, 0, __VA_ARGS__); \
        Logger::instance().flush(); \
        std::terminate(); \
    } \
    while(0)\

#define CORE_ERROR(...) \
    do {\
        Logger::instance().log("ERROR", NULL, NULL, 0, __VA_ARGS__); \
        Logger::instance().flush(); \
    } \
    while(0)\

#define CORE_WARNING(...) \
    do {\
        Logger::instance().log("\x1B[33mWARNING", NULL, NULL, 0, __VA_ARGS__);\
    } \
    while(0)\

#define CORE_WARN(...) \
    do {\
        Logger::instance().log("WARNING", NULL, NULL, 0, __VA_ARGS__);\
    } \
    while(0)\

// Release mode definitions of macros. Defined in such a way as to be
// ignored completelly by the compiler
#define CORE_DEBUG(...) do { (void)sizeof(__VA_ARGS__); } while(0)
#define CORE_VERBOSE(...) do { (void)sizeof(__VA_ARGS__); } while(0)
#define CORE_LOG(tag, ...) do { (void)sizeof(__VA_ARGS__); } while(0)
#define CORE_ASSERT(expr) do { (void)sizeof(expr); } while(0)

#endif

#define CORE_INFO(...) \
    do {\
        Logger::instance().log("INFO", __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); \
    } \
    while(0) \

#endif /* _LOGGER_H_ */
