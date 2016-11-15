#ifndef _SHIP_H
#define _SHIP_H

#include "Unit.h"

class Ship : public Unit {
public:
	// Ship ctor and dtor //////////////////////////////////////////////////////

	// Ship ctor
	// map - Map this Unit is a part of
	// x - X coord of the world to create this Unit at
	// y - Y coord of the world to create this Unit at 
	// s - Stats this Unit will use
	// lvlDiff - Stats to gain each level
	Ship(Map* map, float x, float y, Stats s, Stats lvlDiff);

	// Ship ctor
	// map - Map this Unit is a part of
	// x - X coord of the world to create this Unit at
	// y - Y coord of the world to create this Unit at 
	// s - Stats this Unit will use
	// lvlDiff - Stats to gain each level
	// size - Size in pixels of this Unit
	// sides - How many sides this Unit has
	// c - Color to draw this Unit
	Ship(Map* map, float x, float y, Stats s, Stats lvlDiff,
		int size, int sides, sf::Color c);

	// Methods /////////////////////////////////////////////////////////////////

	// Get how many sides this Ship has
	// returns: How many sides this Ship has
	int getSideCount() const { return _shape.getPointCount(); }

	// Get the color of this Ship
	// returns: The color of this Ship. The Color determines the level relative
	//		to the player's Ship
	const sf::Color& getColor() const { return _shape.getFillColor(); }

	// Set the color of the Ship's _shape
	// c - New color to use
	void setColor(sf::Color c) { _shape.setFillColor(c); }

protected:
};

#endif
