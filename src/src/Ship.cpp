#include "Ship.h"

// =============================================================================
// Ctor and Dtor
// =============================================================================
Ship::Ship() :
		Ship(nullptr, 0.0f, 0.0f, 0, Stats()) {

}

//
Ship::Ship(Map* map, float x, float y, int collRadius, Stats s)
	: Ship(map, x, y, collRadius, s, 30, sf::Color::Red) {
	
}

//
Ship::Ship(Map* map, float x, float y, int collRadius, Stats s,
		int sides, sf::Color color)
 	: Unit(map, x, y, collRadius, s) {
	
	_shape.setRadius(collRadius);
	_shape.setPointCount(sides);
	_shape.setFillColor(color);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(-3.0f);
}

Ship::~Ship() {

}
