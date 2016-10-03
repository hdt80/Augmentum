#ifndef _UNIT_H
#define _UNIT_H

#include "Object.h"

class Unit : public Object {
public:
	Unit();
	Unit(Map* map, float x, float y, Stats s);
	virtual ~Unit();

	virtual float& getHealth() { return _health; }
	virtual float& getMaxHealth() { return _maxHealth; }

protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	float _health; // Current health of this Unit
	float _maxHealth; // Max health this Unit can have
};

#endif
