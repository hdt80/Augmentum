#include "Cursor.h"

#include <cmath>
#include "Convert.h"
#include "Game.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////
Cursor::Cursor() {
	int points = 20;
	int radius = 2; // pixels

	_vertArray.setPrimitiveType(sf::LineStrip);
	_vertArray.resize(points);

	int angle = 0;
	for (int i = 0; i < points; ++i) {
		angle = convert::toRad(360 / (points * i + 1));	
		
		// std uses rad
		_vertArray[i].position.x = _x + radius + std::cos(angle);
		_vertArray[i].position.y = _y + radius + std::sin(angle);
		_vertArray[i].color = sf::Color(128, 128, 128);
	}
}

Cursor::~Cursor() {

}
////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Cursor::setPosition(float x, float y) {
	_x = x;
	_y = y;

	for (unsigned int i = 0; i < _vertArray.getVertexCount(); ++i) {
		_vertArray[i].position.x = _x;
		_vertArray[i].position.y = _y;
	}
}

void Cursor::update(int diff) {
	sf::Vector2i pos = sf::Mouse::getPosition(Game::getRenderWindow());

	setPosition(pos.x, pos.y);

	CORE_INFO("Mouse pos %g %g", getX(), getY());
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_vertArray);	
}
