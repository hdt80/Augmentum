#include "Logger.h"

#include <string.h>
#include <stdarg.h>
#include <iostream>

void CORE_INFO(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	CORE_LOG("INFO", Colors::CYAN, fmt, args);
	va_end(args);
}
void CORE_WARN(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	CORE_LOG("WARN", Colors::YELLOW, fmt, args);
	va_end(args);
}
void CORE_WARNING(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	CORE_LOG("WARN", Colors::YELLOW, fmt, args);
	va_end(args);
}
void CORE_ERROR(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	CORE_LOG("ERRO", Colors::LIGHT_RED, fmt, args);
	va_end(args);
}
void CORE_FATAL(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	CORE_LOG("FATL", Colors::RED, fmt, args);
	va_end(args);
}
void CORE_DEBUG(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	CORE_LOG("DBUG", Colors::MAGENTA, fmt, args);
	va_end(args);
}

// Since we can't pass vargs, we need to construct a list of them before
// passing them along
void CORE_LOG(const char* tag, trmclr::Style color,
		const char* fmt, va_list args) {


	// By using a stringstream we can avoid using std::cout, which will catch
	// the color formatting when redirecting it to the console, which isn't
	// very useful to the console. It probably is a bad idea to do this, but
	// this is a temporary thing until the console collects CORE_* output too
	
	std::stringstream clrss;
	clrss << color;

	std::stringstream defss;
	defss << Colors::DEFAULT;

	fprintf(stdout, "[%s%s%s] ", clrss.str().c_str(), tag, defss.str().c_str());
	vfprintf(stdout, fmt, args);
	fprintf(stdout, "\n");
	va_end(args);
}
