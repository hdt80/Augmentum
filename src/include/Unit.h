#ifndef _UNIT_H
#define _UNIT_H

#include "Object.h"

class Unit : public Object {
public:
	Unit();
	Unit(Map* map, float x, float y, Stats s);
	virtual ~Unit();

protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	int _health; // Current health of this Unit
	int _maxHealth; // Max health this Unit can have
};

#endif
