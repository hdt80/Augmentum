#ifndef _STRING_UTIL_H
#define _STRING_UTIL_H

#include <string>
#include <vector>
#include <sstream>
#include <memory>

// Used to get the current working directory
#ifdef _WIN32
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

namespace StringUtil {

	// Format a string similar to how printf does
	// format - String to format
	// args - Arguments to format in
	// returns: A formatted string like how prinf would format it
	template<typename ... Args>
	std::string format(const std::string& format, Args ... args) {
		size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);
		// Remove the terminating character
		return std::string(buf.get(), buf.get() + size - 1);
	}

	// Convert an object to a std::string
	// n - Object to convert
	// returns: A string representation of the object
	template<typename T> 
	std::string toString(const T& n) {
		std::ostringstream stream;
		stream << n;
		return stream.str();
	}

	// Split a string into a vector delimited by the delim char
	// str - String to split
	// delim - Deliminating character, character to split on
	// returns: A vector of the string split on the delim char. The delim chars
	//		are not included
	std::vector<std::string> split(const std::string& str, char delim);

	// Convert a string to an int
	// str - String to convert to an int
	// returns: An int representation of the string
	int toInt(const std::string& str);

	// Get the directory that the program is running from
	// returns: The absolute directory the program is running in
	std::string getWorkingDir();
};

#endif
