#include "Logger.h"

#include <sstream>

namespace LogColor {
	char CLEAR[]	= {0x1b, '[', '0', '3', '0', 'm', 0};
	char RESET[]	= {0x1b, '[', '0', '3', '9', 'm', 0};
	char RED[]		= {0x1b, '[', '0', '3', '1', 'm', 0};
	char GREEN[]	= {0x1b, '[', '0', '3', '2', 'm', 0};
	char YELLOW[]	= {0x1b, '[', '0', '3', '3', 'm', 0};
	char BLUE[]		= {0x1b, '[', '0', '3', '4', 'm', 0};
	char MAGENTA[]	= {0x1b, '[', '0', '3', '5', 'm', 0};
	char CYAN[]		= {0x1b, '[', '0', '3', '6', 'm', 0};
	char WHITE[]	= {0x1b, '[', '0', '3', '7', 'm', 0};
};

////////////////////////////////////////////////////////////////////////////////
// Logger class
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

Logger::Logger()
	: _output(stdout) {}

Logger::~Logger() {
	// Don't close stdout
	if (_output != stdout) {
		fclose(_output);
	}
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Logger::log(const std::string& tag, const char* color,
	const char* func, const char* src, unsigned int line,
	const std::string& fmt, ...) {

	// Information about the message (source file, line number, etc)
	std::string messageInfo = "| ";

	// Tag used to ID the message (INFO, etc)
	std::string coloredTag = "";

	// If any messageInfo was provided, and a new line should be printed
	// after fmt for better clarity
	bool newline = false;

	// No color, just print the tag
	if (color == nullptr) {
		coloredTag = '[' + tag + ']';
	} else {
		// Must be two lines
		coloredTag = "[";
		coloredTag += color + tag + LogColor::RESET;
		coloredTag += "] ";
	}

#if defined(LOGGER_USE_FILE)
	if (src != nullptr) {
		fprintf(_output, "<%-40s> ", src);
		newline = true;
	}
#endif // LOGGER_USE_FILE

#if defined(LOGGER_USE_FUNCTION) && defined(LOGGER_USE_LINE)
	if (func != nullptr && line > 0) {
		fprintf(_output, "%40s:%d", func, line);
		newline = true;
	}
#endif // LOGGER_USE_FUNCTION && LOGGER_USE_LINE

	if (newline == true) {
		fprintf(_output, "\n");
	}

	// Add the unformatted string that will be formatted
	coloredTag += fmt + '\n';

	// Char pointer to the output which can be used by va_list
	const char* coloredTagp = coloredTag.c_str();

	va_list arg;
	va_start(arg, coloredTagp);

	vfprintf(_output, coloredTagp, arg);

	// Print the new line if needed
	if (newline) {
		fprintf(_output, "\n");
	}

	va_end(arg);
}

std::string Logger::methodName(const std::string& func,
	const std::string& pfunc) {

	// If input is a constructor it gets the class name, not the method
	size_t locFuncName = pfunc.find(func);

	// Find where the class name starts, after the return types
	size_t begin = pfunc.rfind(" ", locFuncName) + 1;

	// Find where the function name starts and class name ends
	size_t end = pfunc.find("(", locFuncName + func.length());

	// Add the ... to indicate the method takes arguments
	if (pfunc[end + 1] == ')') {
		return (pfunc.substr(begin, end - begin) + "()");
	} else {
		return (pfunc.substr(begin, end - begin) + "(...)");
	}
}
