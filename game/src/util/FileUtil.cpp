#include "game/util/FileUtil.h"

#include "logger/Logger.h"

#include <tinydir.h>

#include <regex>

namespace FileUtil {

	bool isFile(const std::string& path) {
		tinydir_dir dir;
		tinydir_open(&dir, path.c_str());

		tinydir_file file;
		tinydir_readfile(&dir, &file);

		bool isFile = !file.is_dir;

		tinydir_close(&dir);

		return isFile;
	}

	bool isDirectory(const std::string& path) {
		// Since tinydir has tinydir_file.is_dir, a path can only be either a
		// file or a directory. If the path is not a file, therefore is must be
		// a path, which allows isDirectory(path) == !isFile(path);
		return !isFile(path);
	}

	std::vector<std::string> getFiles(const std::string& path,
		const std::string& pattern) {

		std::vector<std::string> files;
		std::regex regex(pattern);

		tinydir_dir dir;
		// Have to open it sorted to get all the files at the path
		tinydir_open_sorted(&dir, path.c_str());

		for (unsigned int i = 0; i < dir.n_files; ++i) {
			tinydir_file file;
			tinydir_readfile_n(&dir, &file, i);

			if (!file.is_dir) {
				if (std::regex_match(file.name, regex)) {
					files.push_back(file.name);
				} else {
					AG_INFO("%s does not match %s", file.name, pattern.c_str());
				}
			}
		}

		tinydir_close(&dir);

		return files;
	}
};
