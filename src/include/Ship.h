#ifndef _SHIP_H
#define _SHIP_H

#include "Unit.h"

class Ship : public Unit {
public:
	//
	Ship(Map* map, float x, float y, Stats s);
	//
	Ship(Map* map, float x, float y, Stats s, int sides, sf::Color c);

	// Get how many sides this Ship has
	// returns: How many sides this Ship has
	int getSideCount() const { return _shape.getPointCount(); }

	// Get the color of this Ship
	// returns: The color of this Ship. The Color determines the level relative
	//		to the player's Ship
	const sf::Color& getColor() { return _shape.getFillColor(); }

	// Set the color of the Ship's _shape
	// c - New color to use
	void setColor(sf::Color c) { _shape.setFillColor(c); }

protected:
};

#endif
