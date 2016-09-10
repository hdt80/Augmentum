#include "Convert.h"

namespace convert {

	// Split a string into a vector of string delimited by the delimiter char
	// str - String to be split into the vector
	// delim - Character to delimit
	// Returns - A vector of strings split by the delim char
	std::vector<std::string> split(std::string str, char delim) {
		std::vector<std::string> toReturn;
		std::stringstream ss(str);
		std::string item;
		while (std::getline(ss, item, delim)) {
			toReturn.push_back(item);
		}
		return toReturn;
	}

	// Convert a string to an int
	// str - String to be converted
	// Returns - An int value of the string
	int toInt(std::string str) {
		return strtol(str.c_str(), nullptr, 10);
	}

	std::string getWorkingDir() {
		char path[FILENAME_MAX];
		if (!GetCurrentDir(path, sizeof(path))) {
			return "";
		}
		path[sizeof(path) - 1] = '\0';
		return path;
	}

	// Linear interpolation
	// max - Max value to approach
	// cur - Current value
	// dt - Delta time (seconds), how much to advance the value
	float approach(float max, float cur, float dt) {
		float diff = max - cur;

		if (diff > dt) {
			return cur + dt;
		}
		if (diff < -dt) {
			return cur - dt;
		}
		return max;
	}
}
