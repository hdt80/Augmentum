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

	fprintf(stdout, "[");
	std::cout << color;
	fprintf(stdout, tag);
	std::cout << Colors::DEFAULT;
	fprintf(stdout, "] ");
	vfprintf(stdout, fmt, args);
	fprintf(stdout, "\n");
	va_end(args);
}
