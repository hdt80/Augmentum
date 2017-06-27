#include "game/Console.h"

#include "game/Database.h"
#include "game/Databases.h"
#include "game/Game.h"
#include "game/Ship.h"
#include "game/Enemy.h"
#include "game/environment/Asteroid.h"
#include "game/Projectile.h"
#include "game/util/SFMLUtil.h"
#include "game/util/ObjectUtil.h"

#include "lua/LuaScript.h"
#include "lua/LuaDefines.h"

#include "util/UtilString.h"

#include <cctype>
#include <cstdio>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Console ctor and dtor
////////////////////////////////////////////////////////////////////////////////

Console::Console()
	: _cursorPos(0) {

	_inputText.setFont(Databases::Fonts.getDefault());
	_inputText.setCharacterSize(16);
	_inputText.setFillColor(sf::Color::White);
	_inputText.setOutlineColor(sf::Color::Black);
	_inputText.setOutlineThickness(1.0f);
	_inputText.setPosition(4, Game::getSize().Y - 32);
}

Console::~Console() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Lua state methods
////////////////////////////////////////////////////////////////////////////////

void Console::loadLua() {
	_lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table,
		sol::lib::package, sol::lib::math, sol::lib::debug);

	LuaDefines::defineClasses(_lua);

	// All objects to be reference in the Console must be defined in here
	_lua.set("map", &Game::getMap()); // Have to pass the pointer
	_lua.set("ship", Game::getMap().getSelected());
}

void Console::executeCommand(const std::string& cmd) {
	addHistoryLine(cmd);
	addOutput("> " + cmd);

	_redirect.startRedirect();

	// Run the command
	try {
		_lua.script(cmd);
	} catch (const sol::error& e) {
		addOutput(e.what());
	}

	_redirect.endRedirect();

	std::string scout = _redirect.getCout();
	std::string stdcout = _redirect.getStdout();

	if (scout.size() > 0) {
		addOutput(scout);
	}

	if (stdcout.size() > 0) {
		addOutput(stdcout);
	}
}

void Console::addObject(void* obj) {
	_lua.set(ag::String::format("0x%X", obj), obj);
}

void Console::addNamedObject(const std::string& name, void* obj) {
	_lua.set(name, obj);
}

////////////////////////////////////////////////////////////////////////////////
// Control methods
////////////////////////////////////////////////////////////////////////////////

void Console::handleEvent(const sf::Event& e) {
	if (e.type == sf::Event::TextEntered) {
		handleTextEvent(e);
	} else if (e.type == sf::Event::KeyPressed) {
		handleKeyEvent(e);
	} else if (e.type == sf::Event::MouseButtonReleased) {
		handleMouseEvent(e);
	}

	// Add a | where the cursor is
	sf::String dispStr(_input);
	dispStr.insert(_cursorPos, '|');
	dispStr.insert(0, "> ");
	_inputText.setString(dispStr);
}

void Console::handleKeyEvent(const sf::Event& e) {
	if (e.type == sf::Event::KeyPressed) {
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
	}
}

void Console::handleTextEvent(const sf::Event& e) {
	if (e.type == sf::Event::TextEntered) {
		char c = static_cast<char>(e.text.unicode);
		// Any character that is printable as defined by the locale
		// This is digits, letters, punctuation and space
		if (std::isprint(c) && c != '`') {
			_input.insert(_cursorPos++, 1, c);
		}
	}
}

void Console::handleMouseEvent(const sf::Event& e) {
	if (e.type == sf::Event::MouseButtonReleased) {
		Vector2 relPos = SFMLUtil::getRelativeMouseClick(
			e.mouseButton.x, e.mouseButton.y, Game::CurrentWindow);

		Object* object = Game::getMap().objectAt(nullptr, relPos.X, relPos.Y);

		// Try to upcast the clicked object as much as possible so sol
		// can use the proper userdata supplied from LuaDefine*
		if (ObjectUtil::isType<Unit>(object)) {
			if (ObjectUtil::isType<Enemy>(object)) {
				_lua.set("mouse", ObjectUtil::toType<Enemy>(object));
			} else if (ObjectUtil::isType<Ship>(object)) {
				_lua.set("mouse", ObjectUtil::toType<Ship>(object));
			} else if (ObjectUtil::isType<Asteroid>(object)) {
				_lua.set("mouse", ObjectUtil::toType<Asteroid>(object));
			} else {
				_lua.set("mouse", ObjectUtil::toType<Unit>(object));
			}
		} else if (ObjectUtil::isType<Projectile>(object)) {
			_lua.set("mouse", ObjectUtil::toType<Projectile>(object));
		} else {
			_lua.set("mouse", object);
		}
	}
}

void Console::addOutput(const std::string& line) {
	sf::Text text(line, Databases::Fonts.getDefault(), 16);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1.0f);

	for (const sf::String& str : SFMLUtil::wrapText(text, Game::getSize().X)) {
		sf::Text addingText(text);
		addingText.setString(str);
		_output.insert(_output.begin(), addingText);
	}

	for (unsigned int i = 0; i < _output.size(); ++i) {
		sf::Text& iter = _output[i];

		// Add one to the position because the current line is on 0
		iter.setPosition(4, Game::getSize().Y - 32 - (24 * (i + 1)));
	}
}

void Console::addHistoryLine(const std::string& line) {
	_cmdHistory.insert(_cmdHistory.begin(), line);
}

void Console::setOpened(bool b) {
	_opened = b;

	Game::getRenderWindow().setMouseCursorVisible(_opened);
}

void Console::setPosition(const Vector2& size) {
	_inputText.setPosition(4, size.Y - 32);
}

void Console::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (isOpened()) {
		target.draw(_inputText);
		for (const sf::Text& text : _output) {
			// If the text isn't on screen all the text after this won't
			// be either, so don't bother drawing it
			if (text.getPosition().y + text.getLocalBounds().height < 0) {
				return;
			}
			target.draw(text);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// Static vars
////////////////////////////////////////////////////////////////////////////////

sf::Keyboard::Key Console::HOTKEY = sf::Keyboard::Tilde;
