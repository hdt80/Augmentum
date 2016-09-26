#ifndef UTIL_CONVERT_H
#define UTIL_CONVERT_H

#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <memory>
#include <iostream>

#ifdef WINDOWS
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

namespace convert {

	const float B2BOX_SCALE = 30.f;

	template<typename T> 
	std::string toString(const T& n) {
		std::ostringstream stream;
		stream << n;
		return stream.str();
	}

	// Split a string into a vector delimited by the delim char
	std::vector<std::string> split(std::string str, char delim);

	// Convert a string to an int
	int toInt(std::string str);

	std::string getWorkingDir();

	float approach(float max, float cur, float dt);

	template<typename ... Args>
	std::string format(const std::string& format, Args ... args) {
		size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1);
	}

	// Convert radians to degrees
	inline float toDeg(float rad) { return rad * 57.295779; }
	// Convert degrees to radians
	inline float toRad(float deg) { return deg * 0.0174532; }

	// Box2d uses a smaller scale than our game, by a factor of 10
	inline float toB2(float f) { return f / B2BOX_SCALE; }
	inline float fromB2(float f) { return f * B2BOX_SCALE; }
}

#endif
