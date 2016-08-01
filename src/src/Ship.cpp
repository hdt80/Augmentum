#include "Ship.h"

// =============================================================================
// Ctor and Dtor
// =============================================================================
Ship::Ship() {
	Ship(nullptr, 0.0f, 0.0f, 0, Stats());
}

Ship::Ship(Map* map, float x, float y, int collRadius, Stats s)
	: Unit(map, x, y, collRadius, s) {
	
	_shape.setRadius(15);
	_shape.setFillColor(sf::Color::Green);
}

Ship::~Ship() {

}
