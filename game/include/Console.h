#pragma once

#include "game/Vector2.h"
#include "game/OutputRedirect.h"

#include "logger/Logger.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <sol/sol.hpp>

#include <string>

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

	// Add a line of text to the history
	// line - Line of text to add
	void addHistoryLine(const std::string& line);

	// Add a line of text to the output
	// line - Line of text to add
	void addOutput(const std::string& line);

	// Static vars /////////////////////////////////////////////////////////////
	
	static sf::Keyboard::Key HOTKEY; // Hotkey used to open the Console

protected:

	// Inherited from sf::Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Event handlers //////////////////////////////////////////////////////////

	// Handle any key event
	// e - Event to handle
	void handleKeyEvent(const sf::Event& e);

	// Handle any text event
	// e - Event to handle
	void handleTextEvent(const sf::Event& e);

	// Handle any mouse event
	// e - Event to handle
	void handleMouseEvent(const sf::Event& e);

	// Vars ////////////////////////////////////////////////////////////////////
	
	// Object used to redirect the output from std::cout and stdout
	OutputRedirect _redirect;

	sol::state _lua; // Lua object to call the commands on

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
