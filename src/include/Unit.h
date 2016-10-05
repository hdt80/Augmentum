#ifndef _UNIT_H
#define _UNIT_H

#include "Object.h"

class Unit : public Object {
public:
	Unit();
	Unit(Map* map, float x, float y, Stats s, int sides, sf::Color c);
	virtual ~Unit();

	// Health getters and setters //////////////////////////////////////////////

	// Get the current health of this Unit
	// returns: Current health of this Unit
	inline float& getHealth() { return _health; }

	// Get the max health this Unit can have
	// returns: Max health of this Unit
	inline float& getMaxHealth() { return _maxHealth; }
	
	// Get how much health is missing
	inline float getHealthGone() { return _maxHealth - _health; }

	// Set the current health of this Unit
	// h - New health of this Unit
	virtual void setHealth(float h) { _health = h; }
	
	// Set the max health a Unit can have
	// h - Max health of this unit
	virtual void setMaxHealth(float h) { _maxHealth = h; }

	// Exp helper methods //////////////////////////////////////////////////////

	// Get the exp till the next level is reached
	// returns: How much exp is needed till the next level is hit
	int getExpToNextLevel();

	// Get the current level of this Unit
	// returns: The current level of this Unit
	int getLevel();

	// Get the current amount of exp this Unit has
	// returns: The exp of this Unit
	float getExp();

protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	float _health; // Current health of this Unit
	float _maxHealth; // Max health this Unit can have

	float _exp; // Current experience of this Unit
};

#endif
