#ifndef UTIL_CONVERT_H
#define UTIL_CONVERT_H

#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>

#ifdef WINDOWS
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

struct HSVColor {
    double h; // angle in degrees
    double s; // percent
    double v; // percent
};

namespace HSVConvert {

	// Convert an RGB color to an HSL
	// r - R value, percent
	// g - G value, percent
	// b - B value, percent
	// returns: The HSLColor equivalant
	HSVColor RGBToHSV(double r, double g, double b);

	// Convert an HSL Color to an RGB
	// h - Hue, angle in degrees
	// s - Saturation in percent
	// v - Value in percent
	sf::Color HSVToRGB(double h, double s, double v);

};

namespace convert {

	const float B2BOX_SCALE = 30.f;

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
	std::vector<std::string> split(std::string str, char delim);

	// Convert a string to an int
	int toInt(std::string str);

	// Get the directory that the program is running from
	// returns: The absolute director the program is running in
	std::string getWorkingDir();

	// Linearly interpolate to a value
	// max - Max value to approach
	// cur - Current value 
	// dt - Deltatime, how much to interpolate
	float approach(float max, float cur, float dt);

	// Interpolate between two colors
	// min - Min color, when t = 0
	// max - Max color, when t = 1
	// t - Percent to interpolate as in decimal form
	sf::Color colorInterpolate(sf::Color min, sf::Color max, float t);

	// Linearly interpolate to a value
	// max - Max value to approach
	// cur - Current value 
	// dt - Deltatime, how much to interpolate
	int linearInterpolate(float max, float cur, float dt);

	// Format a string similar to how printf does
	// format - String to format
	// args - Arguments to format in
	template<typename ... Args>
	std::string format(const std::string& format, Args ... args) {
		size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1);
	}

	// Convert radians to degrees
	// rad - Angle in radians
	// returns: The equivalent angle in degrees
	inline float toDeg(float rad) { return rad * 57.295779; }

	// Convert degrees to radians
	// deg - Angle in degrees
	// returns: The equivalent angle in radians
	inline float toRad(float deg) { return deg * 0.0174532; }

	// Box2d uses a smaller scale than our game, by a factor of 10
	inline float toB2(float f) { return f / B2BOX_SCALE; }
	inline float fromB2(float f) { return f * B2BOX_SCALE; }
}

#endif
