#ifndef _UNIT_H
#define _UNIT_H

#include "Object.h"
#include "Cooldown.h"

class Unit : public Object {
public:
	Unit();
	Unit(Map* map, float x, float y, Stats s, int sides, sf::Color c);
	virtual ~Unit();

	// Methods /////////////////////////////////////////////////////////////////

	// Simulate the update for an amount of time
	// diff - Microseconds to simulate the Unit for
	void update(int diff);

	// Events //////////////////////////////////////////////////////////////////
	
	// Occurs when the Unit levels up
	virtual void onLevelUp();

	// Shooting methods ////////////////////////////////////////////////////////
	
	// Check if this Unit can shoot
	// returns: If the _reload Cooldown is completed
	inline bool canShoot() { return _reload.done(); }

	// Shoot towards a point
	// x - X coord of the Map to shoot at
	// y - Y coord of the Map to shoot at
	void shoot(float x, float y);

	// Shoot towards a Target
	// target - Target to shoot towards
	void shoot(Target* target);

	// Stats ///////////////////////////////////////////////////////////////////
	
	virtual float getStat(const std::string& name) const;

	// Health getters and setters //////////////////////////////////////////////
	
	// Apply damage to a unit
	// d - Damage applied. Negative damage will heal
	// hitter - What Unit shot this Unit
	void applyDamage(float d, Unit* hitter);

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
	float getExpToNextLevel() const;

	// Get how much exp this Unit has for the current level
	// returns: How much exp the Unit has towards the current level
	float getExpForCurrentLevel() const;

	// Get the current level of this Unit
	// returns: The current level of this Unit
	int getLevel() const;

	// Get the current amount of exp this Unit has
	// returns: Reference to exp of this Unit
	inline float& getExp() { return _exp; }

	// Get the current amount of exp this Unit has
	// returns: The exp of this Unit
	inline float getExp() const { return _exp; }

	// Add exp to a unit
	// e - Amount of exp to add
	inline void addExp(float e) { _exp += e; }

	// Set the exp of a unit
	// e - How much exp this unit will have
	inline void setExp(float e) { _exp = e; }

	// Set the level of this Unit
	// level - Level to set the Unit to
	void setLevel(int level);

protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	Cooldown _reload; // Time till you can shoot again

	Stats _levelDiff; // How much the stats will grow each level

	float _health; // Current health of this Unit
	float _maxHealth; // Max health this Unit can have

	float _exp; // Current experience of this Unit
	int _prevLevel; // Used to check if the Unit has gone up a level
};

#endif
