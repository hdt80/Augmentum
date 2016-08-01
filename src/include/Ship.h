#ifndef _SHIP_H
#define _SHIP_H

#include "Unit.h"

class Ship : public Unit {
public:
	Ship(Map* map, float x, float y, int collRadius, Stats s);
	Ship();
	~Ship();

protected:

};

#endif
