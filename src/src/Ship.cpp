#include "Ship.h"
#include "Map.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and Dtor
////////////////////////////////////////////////////////////////////////////////

Ship::Ship(Map* map, float x, float y, Stats s, Stats lvlDiff)
	: Ship(map, x, y, s, lvlDiff, 20, 30, sf::Color::Red) {
	
}
Ship::Ship(Map* map, float x, float y, Stats s,	Stats lvlDiff,
		int size, int sides, sf::Color color)
 	: Unit(map, x, y, s, lvlDiff, size, sides, color) {

	if (_b2Box) {
		_b2Box->SetUserData(this);
	}
}

Ship::~Ship() {
	// Deleting a Box2D body by calling the dtor will break a lot of things
	if (_b2Box) {
		_map->getWorld()->DestroyBody(_b2Box);
		_b2Box = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////
