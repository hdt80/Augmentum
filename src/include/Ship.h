#ifndef _SHIP_H
#define _SHIP_H

#include "Unit.h"

class Ship : public Unit {
public:
	//
	Ship(Map* map, float x, float y, Stats s);
	//
	Ship(Map* map, float x, float y, Stats s, int sides, sf::Color c);

	int getSideCount() const { return _sides; }
	const sf::Color& getColor() { return _color; }

protected:

	int _sides; // Number of sides on this Ship
	sf::Color _color; // Color of the Ship
};

#endif
