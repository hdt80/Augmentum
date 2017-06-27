#include "game/Cursor.h"

#include "game/Game.h"

#include "util/UtilMath.h"

#include <cmath>

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

Cursor::Cursor()
	: _x(0.0f), _y(0.0f) {

	float points = 20;
	float radius = 2; // pixels

	_vertArray.setPrimitiveType(sf::TriangleFan);
	_vertArray.resize(points);

	float angle = 0;
	for (int i = 0; i < points; ++i) {
		if (i == 0) {
			angle = 0;
		} else {
			angle = ag::Math::degToRad((360 / points) * i);	
		}
		
		// std uses radians
		_vertArray[i].position.x = _x + radius * std::cos(angle);
		_vertArray[i].position.y = _y + radius * std::sin(angle);
		_vertArray[i].color = sf::Color(255, 0, 0);
	}

	_origVert = _vertArray;
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
		_vertArray[i].position.x = _origVert[i].position.x + _x;
		_vertArray[i].position.y = _origVert[i].position.y + _y;
	}
}

void Cursor::update(int diff) {
	sf::Vector2i pos = sf::Mouse::getPosition(Game::getRenderWindow());

	setPosition(pos.x, pos.y);
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_vertArray);	
}
