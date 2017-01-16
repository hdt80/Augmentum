#include "OutputRedirect.h"

#include "Logger.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

OutputRedirect::OutputRedirect() {
	// Save the original streams used before the console redirects the output
	_coutOrig = std::cout.rdbuf();
	_cerrOrig = std::cerr.rdbuf();
}

OutputRedirect::~OutputRedirect() {
	endRedirect();
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void OutputRedirect::startRedirect() {
	// Create the pipe
	if (pipe(fdStdoutPipe) != 0) {
		CORE_ERROR("pipe returned non zero");
	}

	// Redirect all output back to the console
	_cout = std::cout.rdbuf(_outBuffer.rdbuf());
	_cerr = std::cerr.rdbuf(_errBuffer.rdbuf());

	// Save a copy of stdout so we can restore to it later
	fdStdout = dup(fileno(stdout));

	// Redirect stdout to our pipe
	dup2(fdStdoutPipe[MFD_WRITE], fileno(stdout));
	
	// Set up the stream for reading
	setvbuf(stdout, NULL, _IONBF, 0);

	// This print right here is very important. Without this, nothing is put
	// into stdout's buffer, causing the _read to hang, because there is
	// nothing to read. Because of this, any reads with a single space mean
	// that the script didn't print anything, so don't bother forwarding
	// the single space to the console
	printf(" ");
}

void OutputRedirect::endRedirect() {
	// Restore the iostreams to normal
	std::cout.rdbuf(_coutOrig);
	std::cerr.rdbuf(_cerrOrig);

	// Reset stdout
	fflush(stdout);

	// Reset stdout back to it's original state
	dup2(fdStdout, fileno(stdout));
	close(fdStdout); // Close the redirected stdout
}

std::string OutputRedirect::getCout() {
	return _outBuffer.str();
}

std::string OutputRedirect::getStdout() {
	char buffer[1024];
	int n = read(fdStdoutPipe[MFD_READ], buffer, 1024);
	buffer[n] = '\0'; // Add the null terminating char

	// n is 1 only when the blank space is output when the output is first being
	// redirected, so don't bother returning the space, just a blank string
	if (n == 1) {
		return std::string();
	}

	// Add 1 for the \0 and ignoring the space printed when first starting
	return std::string(buffer + 1);
}
