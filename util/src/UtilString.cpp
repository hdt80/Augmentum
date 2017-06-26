#include "util/UtilString.h"

namespace ag {

namespace String {

	std::vector<std::string> split(const std::string& str, char delim) {
		std::vector<std::string> toReturn;
		std::stringstream ss(str);
		std::string item;
		while (std::getline(ss, item, delim)) {
			toReturn.push_back(item);
		}
		return toReturn;
	}

	int toInt(const std::string& str) {
		return strtol(str.c_str(), nullptr, 10);
	}

}; // namespace ag::String

}; // namespace ag
