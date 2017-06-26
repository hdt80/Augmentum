#pragma once

// Used for getting the current working directory
#if defined(_WIN32)
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif // defined(_WIN32)

#include <vector>
#include <string>

namespace ag {

namespace File {

// Check if an item at a path is a file
//
// path - Path to check for. The path will be relative to the current working
//		directory of the executing program
//
// returns: If the path resolves to a path is a file
//
bool isFile(const std::string& path);

// Check if an item at a path is a directory
//
// path - Path to check for. The path will be relative to the current working
//		directory of the executing program
//
// returns: If the path resolves to a directory
//
bool isDirectory(const std::string& path);

// Get all the files at a path that match a certain regex pattern. If the
//		passed path is not a directory this will return an empty
//		std::vector<>. Any directory at the path will not be included in
//		the returned std::vector<>
//
// path - Path to get all the files in. A relative path will be relative to
//		the current working directory of the program
//
// pattern - Regex pattern to match the files with. Any file that does not
//		fit the pattern will not be included into the returned std::vector
//
// returns: A vector with the names of the files at the path
//
std::vector<std::string> getFiles(const std::string& path,
	const std::string& pattern = ".*");

// Get the current working directoy of the process
//
// returns: A std::string containing the current working directory
//
std::string getCurrentWorkingDir();
	

}; // namespace ag::File

}; // namespace ag
