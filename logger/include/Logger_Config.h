#pragma once

////////////////////////////////////////////////////////////////////////////////
// Header information settings
////////////////////////////////////////////////////////////////////////////////

// Comment out the following line to disable function printing. If one is
// defined without the other functions will not print, both the function name
// and line number are required
#define LOGGER_USE_FUNCTION
#define LOGGER_USE_LINE

// Comment out the following line to disable file printing
#define LOGGER_USE_FILE

// Comment out the following line to enable simple messages on G++. This will
// disable the usage of __NICE_FUNC__, which adds a lot of runtime overhead
//#define LOGGER_SIMPLE

// Comment out the following line to disable colored message tags
#define LOGGER_NO_COLOR

////////////////////////////////////////////////////////////////////////////////
// Message colors
////////////////////////////////////////////////////////////////////////////////

#if defined(LOGGER_NO_COLOR)
	#define LOGGER_COLOR_DEBUG	LogColor::MAGENTA
	#define LOGGER_COLOR_INFO	LogColor::GREEN
	#define LOGGER_COLOR_WARN	LogColor::YELLOW
	#define LOGGER_COLOR_ERROR	LogColor::RED
	#define LOGGER_COLOR_FATAL	LogColor::RED
	#define LOGGER_COLOR_LOG	LogColor::BLUE
#else
	#define LOGGER_COLOR_DEBUG	nullptr
	#define LOGGER_COLOR_INFO	nullptr
	#define LOGGER_COLOR_WARN	nullptr
	#define LOGGER_COLOR_ERROR	nullptr
	#define LOGGER_COLOR_FATAL	nullptr
	#define LOGGER_COLOR_LOG	nullptr
#endif // LOGGER_NO_COLOR
