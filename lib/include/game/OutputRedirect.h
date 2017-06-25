#pragma once

#include <string>

#ifndef _WIN32
#include <unistd.h>
#endif // _WIN32

#ifdef _WIN32
#define pipe(X) _pipe(X, 1024, O_BINARY)
#define read _read
#define dup _dup
#define dup2 _dup2
#define fileno _fileno
#endif // _WIN32

#include <fcntl.h>
#include <sstream>
#include <streambuf>

class OutputRedirect {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Nullary ctor for OutputRedirect
	OutputRedirect();

	// Dtor for OutputRedirect
	~OutputRedirect();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Begin redirecting std::cout and stdout to the buffers this OutputRedirect
	//		uses to capture the output fom std::cout and stdout
	void startRedirect();

	// Stop redirecting std::cout and stdout and return them to their original
	//		states.
	void endRedirect();

	// Get the output buffered from std::cout
	// returns: A std::string containing the output of the buffer. If nothing
	//		is stored in the buffer an empty string is returned
	std::string getCout();

	// Get the output buffered from stdout
	// returns: A std::string containing the output of the buffer. If nothing
	//		is stored in the buffer an empty string is returned
	std::string getStdout();

protected:

	// file pipes used to stdout
	int fdStdoutPipe[2];
	int fdStdout;

	// file destcriptor states
	const int MFD_READ = 0;
	const int MFD_WRITE = 1;

	// The output of cout is redirected into the console when the console is
	// opened. This is the stream used to redirect
	// The output of the two streams is redirected into the console when the
	// console is active. These two are the streams that we will redirect
	// into from std::cout and std::cerr
	std::streambuf* _cout;
	std::streambuf* _cerr;

	// Original streams used when the program first started. These are used
	// to redirect the output back to the terminal after the console is closed
	std::streambuf* _coutOrig;
	std::streambuf* _cerrOrig;

	// The stringstreams that std::cout and std::cerr will be redirected into
	// while the console is active
	std::stringstream _outBuffer;
	std::stringstream _errBuffer;
};
