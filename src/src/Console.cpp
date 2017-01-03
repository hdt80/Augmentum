#include "Console.h"

#include "Database.h"
#include "Game.h"
#include "LuaScript.h"

#include <cctype>
#include <cstdio>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Console ctor and dtor
////////////////////////////////////////////////////////////////////////////////

Console::Console()
	: _cursorPos(0) {

	_lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::table);

	LuaScript::defineClasses(_lua);

	_inputText.setFont(*Databases::FontDatabase.getDefault());
	_inputText.setCharacterSize(16);
	_inputText.setFillColor(sf::Color::White);
	_inputText.setOutlineColor(sf::Color::Black);
	_inputText.setOutlineThickness(1.0f);
	_inputText.setPosition(4, Game::getSize().Y - 32);
	
	// Save the original streams used before the console redirects the output
	_coutOrig = std::cout.rdbuf();
	_cerrOrig = std::cerr.rdbuf();
}

Console::~Console() {
	std::cout.rdbuf(_coutOrig);
	std::cerr.rdbuf(_cerrOrig);
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Console::executeCommand(const std::string& cmd) {
	beginRedirect();

	// What the redirected output will be put into
	char buffer[1024];
	std::string output;

	// Run the command
	try {
		_lua.script(cmd);
	} catch (const sol::error& e) {
		output = e.what();
	}

	// Read what was returned
	int n = _read(fdStdoutPipe[MFD_READ], buffer, 1024);
	buffer[n] = '\0'; // Add the null terminating char

	output = _outBuffer.str();

	// Add the results to the history
	
	addHistoryLine(cmd);
	addOutput("> " + cmd);

	// If only one char was read it was the space we printed
	if (n != 1) {
		// Add one to the buffer to avoid the space
		addOutput(std::string(buffer + 1));
	}

	// If there was any output use that
	if (output.size() > 0) {
		addOutput(output);
	}

	endRedirect();
}

void Console::handleEvent(const sf::Event& e) {
	if (e.type == sf::Event::TextEntered) {
		char c = static_cast<char>(e.text.unicode);
		// Any character that is printable as defined by the locale
		// This is digits, letters, punctuation and space
		if (std::isprint(c) && c != '`') {
			_input.insert(_cursorPos++, 1, c);
		}
	} else if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::BackSpace) {
			// Make sure we don't delete if there's no chars
			if (_cursorPos > 0) {
				_input.erase(_input.begin() + --_cursorPos);
			}
		} else if (e.key.code == sf::Keyboard::Delete) {
			// Make sure there is a char to delete
			if (_input.size() >= _cursorPos + 1) {
				_input.erase(_input.begin() + _cursorPos);
			}
		} else if (e.key.code == sf::Keyboard::Return) {
			// Execute the command and add the command to the history
			executeCommand(_input);
			_input.clear();
			_cursorPos = 0;
			_historyIndex = 0;
		} else if (e.key.code == sf::Keyboard::Left) {
			// Move the cursor to the left
			if (_cursorPos > 0) {
				--_cursorPos;
			}
		} else if (e.key.code == sf::Keyboard::Right) {
			// More the cursor to the right
			if (_input.size() > _cursorPos) {
				++_cursorPos;
			}
		} else if (e.key.code == sf::Keyboard::Up) {
			if (_historyIndex < _cmdHistory.size()) {
				_input = _cmdHistory[_historyIndex++];
				_cursorPos = _input.size();

				// Wrap the history back to the most recent one
				if (_historyIndex >= _cmdHistory.size()) {
					_historyIndex = _cmdHistory.size() - 1;
				}
			}
		} else if (e.key.code == sf::Keyboard::Down) {
			if (_historyIndex > 0) {
				_input = _cmdHistory[--_historyIndex];
				_cursorPos = _input.size();
			} else if (_historyIndex == 0) {
				_input = "";
				_cursorPos = 0;
			}
		}
	} else {
		CORE_INFO("Unhandled event type in Console");
	}

	// Add a | where the cursor is
	sf::String dispStr(_input);
	dispStr.insert(_cursorPos, '|');
	dispStr.insert(0, "> ");
	_inputText.setString(dispStr);
}

void Console::addOutput(const std::string& line) {
	sf::Text text(line, *Databases::FontDatabase.getDefault(), 16);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1.0f);

	_output.insert(_output.begin(), text);

	for (unsigned int i = 0; i < _output.size(); ++i) {
		sf::Text& iter = _output[i];

		// Add one to the position because the current line is on 0
		iter.setPosition(4, Game::getSize().Y - 32 - (24 * (i + 1)));
	}
}

void Console::addHistoryLine(const std::string& line) {
	_cmdHistory.insert(_cmdHistory.begin(), line);
}

void Console::beginRedirect() {
	// Create the pipe
	if (_pipe(fdStdoutPipe, 1024, O_BINARY) != 0) {
		CORE_ERROR("pipe returned non zero");
	}

	// Redirect all output back to the console
	_cout = std::cout.rdbuf(_outBuffer.rdbuf());
	_cerr = std::cerr.rdbuf(_errBuffer.rdbuf());

	// Save a copy of stdout so we can restore to it later
	fdStdout = _dup(_fileno(stdout));

	// Redirect stdout to our pipe
	_dup2(fdStdoutPipe[MFD_WRITE], _fileno(stdout));
	
	// Set up the stream for reading
	setvbuf(stdout, NULL, _IONBF, 0);

	// This print right here is very important. Without this, nothing is put
	// into stdout's buffer, causing the _read to hang, because there is
	// nothing to read. Because of this, any reads with a single space mean
	// that the script didn't print anything, so don't bother forwarding
	// the single space to the console
	printf(" ");
}

void Console::endRedirect() {
	// Restore std::cout to normal
	std::cout.rdbuf(_coutOrig);
	std::cerr.rdbuf(_cerrOrig);

	// Reset stdout
	fflush(stdout);

	// Reset stdout back to it's original state
	_dup2(fdStdout, _fileno(stdout));
	_close(fdStdout); // Close the redirected stdout
}

void Console::setPosition(const Vector2& size) {
	_inputText.setPosition(4, size.Y - 32);
}

void Console::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (isOpened()) {
		target.draw(_inputText);
		for (const sf::Text& text : _output) {
			target.draw(text);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// Static vars
////////////////////////////////////////////////////////////////////////////////

sf::Keyboard::Key Console::HOTKEY = sf::Keyboard::Tilde;
