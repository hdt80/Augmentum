#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "Colors.h"
#include "trmclr.hpp"

void CORE_INFO(const char* fmt, ...);
void CORE_WARN(const char* fmt, ...);
void CORE_WARNING(const char* fmt, ...);
void CORE_ERROR(const char* fmt, ...);
void CORE_FATAL(const char* fmt, ...);
void CORE_DEBUG(const char* fmt, ...);
void CORE_LOG(const char* tag, trmclr::Style color, const char* fmt, va_list);

#endif
