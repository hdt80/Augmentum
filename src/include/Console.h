#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "Logger.h"
#include "sol/sol.hpp"
#include "Vector2.h"

#ifndef WIN32
#include <unistd.h>
#endif // WIN32

#ifdef WIN32
#define pipe(X) _pipe(X, 1024, O_BINARY)
#define read _read
#define dup _dup
#define dup2 _dup2
#define fileno _fileno
#define close _close
#endif // WIN32

#include <fcntl.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <sstream>
#include <streambuf>

class Console : public sf::Drawable {
public:

	// Console ctor and dtor ///////////////////////////////////////////////////

	Console();
	~Console();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Execute a command
	// cmd - Command to run
	void executeCommand(const std::string& cmd);

	// Handle an event
	// e - Event to handle
	void handleEvent(const sf::Event& e);

	// Set if the Console is opened or not
	// b - If the Console is opened or not
	inline void setOpened(bool b) { _opened = b; }

	// Check if the Console is opened
	// returns: _opened
	inline bool isOpened() const { return _opened; }

	// Set the the position of the Console based on the size of the window
	void setPosition(const Vector2& size);

	// Static vars /////////////////////////////////////////////////////////////
	
	static sf::Keyboard::Key HOTKEY; // Hotkey used to open the Console

protected:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Add a line of text to the history
	// line - Line of text to add
	void addHistoryLine(const std::string& line);

	// Add a line of text to the output
	// line - Line of text to add
	void addOutput(const std::string& line);

	// Begin redirecting output from the terminal to the console
	void beginRedirect();

	// Stop redirecting output from the terminal to the console
	void endRedirect();

	sol::state _lua; // Lua object to call the commands on

	// file pipes
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

	// If the hotkey has been hit and the console is accepted input
	bool _opened;

	// History of commands. The most recently used command is at index 0
	// with each index representing a command used before the previous one
	std::vector<std::string> _cmdHistory;

	// What part of the history we're browsing thru
	unsigned int _historyIndex;

	// Text to represent the output of the commands
	std::vector<sf::Text> _output;

	unsigned int _cursorPos; // What character is selected
	std::string _input; // Current text being input

	sf::Text _inputText; // Text being drawn to SFML

};

#endif
