#ifndef _SHIP_H
#define _SHIP_H

#include "Unit.h"

class Ship : public Unit {
public:
	//
	Ship(Map* map, float x, float y, int collRadius, Stats s);

	//
	Ship(Map* map, float x, float y, int collRadius, Stats s,
			int sides, sf::Color c);
	Ship();
	~Ship();

protected:

};

#endif
