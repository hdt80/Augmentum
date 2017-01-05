#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "Logger.h"
#include "sol/sol.hpp"
#include "Vector2.h"

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
	
	// Lua manipulation methods ////////////////////////////////////////////////

	// Load sol::state by defining all the classes and variables used
	void loadLua();
	
	// Execute a command
	// cmd - Command to run
	void executeCommand(const std::string& cmd);

	// Add a new object to the lua state. To refer to this object use the syntax
	//		of 0xPOINTER
	// obj - Pointer to the object to add
	void addObject(void* obj);

	// Add a new object to the lua state. To refer to this object use the name
	// name - Name to refer to this object by
	// obj - Pointer to the object to add
	void addNamedObject(const std::string& name, void* obj);
	
	// Control methods /////////////////////////////////////////////////////////

	// Handle an event
	// e - Event to handle
	void handleEvent(const sf::Event& e);

	// Set if the Console is opened or not
	// b - If the Console is opened or not
	void setOpened(bool b);

	// Check if the Console is opened
	// returns: _opened
	inline bool isOpened() const { return _opened; }

	// Set the the position of the Console based on the size of the window
	// size - Size of the Window this Console will be in
	void setPosition(const Vector2& size);

	// Static vars /////////////////////////////////////////////////////////////
	
	static sf::Keyboard::Key HOTKEY; // Hotkey used to open the Console

protected:

	// Inherited from sf::Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Handle any key event
	// e - Event to handle
	void handleKeyEvent(const sf::Event& e);

	// Handle any text event
	// e - Event to handle
	void handleTextEvent(const sf::Event& e);

	// Handle any mouse event
	// e - Event to handle
	void handleMouseEvent(const sf::Event& e);

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
