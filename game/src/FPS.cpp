#include "game/FPS.h"

#include "game/Databases.h"

#include "util/UtilString.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

FPS::FPS()
	: _frame(0), _fps(0), _visible(false) {
	
	_fpsText.setPosition(4, 4);
	_fpsText.setFillColor(sf::Color::White);
	_fpsText.setOutlineColor(sf::Color::Black);
	_fpsText.setOutlineThickness(1.0f);
	_fpsText.setFont(Databases::Fonts.get("pixel"));
}

void FPS::update() {
	if (clock.getElapsedTime().asSeconds() >= 1.f) {
       	_fps = _frame;
       	_frame = 0;
       	clock.restart();

		_fpsText.setString(ag::String::format("%d", _fps));
    }
    ++_frame;
}

void FPS::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_fpsText);
}
