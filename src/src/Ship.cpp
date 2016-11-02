#include "Ship.h"
#include "Map.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and Dtor
////////////////////////////////////////////////////////////////////////////////

// Ship ctor
// map - Map this Ship exists on
// x - X position to create the ship at
// y - Y position to create the ship at
// s - Stats the Ship will have
Ship::Ship(Map* map, float x, float y, Stats s)
	: Ship(map, x, y, s, 20, 30, sf::Color::Red) {
	
}

// Ship ctor
// map - Map this Ship exists on
// x - X position to create the ship at
// y - Y position to create the ship at
// s - Stats the Ship will have
// sides - How many sides this ship will have
// color - What color to draw this Ship
Ship::Ship(Map* map, float x, float y, Stats s,	int size,
		int sides, sf::Color color)
 	: Unit(map, x, y, s, size, sides, color) {

	if (_b2Box) {
		_b2Box->SetUserData(this);
	}
}
