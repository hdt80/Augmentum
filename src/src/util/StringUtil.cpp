#include "util/StringUtil.h"

namespace StringUtil {

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

	std::string getWorkingDir() {
		char path[FILENAME_MAX];
		if (!GetCurrentDir(path, sizeof(path))) {
			return "";
		}
		path[sizeof(path) - 1] = '\0';
		return path;
	}
};
