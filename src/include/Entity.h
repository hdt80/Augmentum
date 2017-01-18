#ifndef _ENTITY_H
#define _ENTITY_H

#include "Object.h"

class Unit;
class Projectile;

// An Entity is an Object with health. Entities can be interacted with, but 
// typically don't do anything besides exist and move. Entities don't deal
// damage to any Entity
// Examples: Asteroids
class Entity : public Object {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Entity ctor
	// map - Map this Entity exists on
	// x - X coord in Map units to spawn the Entity at
	// y - Y coord in Map units to spawn the Entity at
	// size - Diameter of the Entity in Map units
	// maxHealth - Health this Entity starts with
	Entity(Map* map, float x, float y, int size, int maxHealth);

	// Entity dtor
	virtual ~Entity();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Deal damage to the Entity. If the Entity is currently invulerable then
	//		damage cannot be dealt to the Entity. A negative amount dealt
	//		(a heal) will still heal the Entity however.
	// amount - Amount of damage to deal. Negative values will heal the Entity
	//		instead of damaging it, but not heal more than the max health
	// source - What is dealing the damage
	void dealDamage(float amount, Unit* source);

	// Update the position of this Object all all vars
	// x - X coord of the map to update to
	// y - Y coord of the map to update to
	virtual void updatePositon(float x, float y);

	// Events //////////////////////////////////////////////////////////////////
	
	// Occurs when a Projectiles hits this Entity. Note that damage isn't taken
	//		into account here, look at onDamageTaken for that. This event will
	//		fire even if the Entity if invulerable.
	// p - Projectile that hit the Entity
	virtual void onProjectileHit(Projectile* p);

	// Occurs when the Entity takes damage from some Unit. This event will still
	//		fire even if the Entity is currently invulerable, but the damage
	//		will not be dealt.
	// dmg - Amount of damage taken. Negative damage means a heal
	// attacker - Unit that dealt the damage
	virtual void onDamageTaken(int dmg, Unit* attacker);

	// Occurs when the Entity is killed. An Entity is killed when its health
	//		is equal or less than 0. This event is only checked for after
	//		dealDamage is called, and not setHealth.
	virtual void onDeath();

	// Health methods //////////////////////////////////////////////////////////
	
	// Set the current health of the Entity
	// health - Health to set to. If health is larger than the max health then
	//		the health is clamped to max health
	void setHealth(float health);

	// Get the current health of this Entity
	// returns: _health
	inline float getHealth() const { return _health; }

	// Set the max health that this Entity has. If the new max health is less
	//		than the current health the current health will be updated to
	//		reflect the new max health, but if the new max health is greater
	//		than the current health no change to the current health will occur
	// health - Max health the Entity will have
	void setMaxHealth(float health);

	// Get the max health this Entity can have
	// returns: _maxHealth
	inline float getMaxHealth() const { return _maxHealth; }

	// Get if the Entity is currently invulerable
	// returns: _invulerable
	inline bool isInvulerable() const { return _invulerable; }

	// Set the invulerable flag of the Entity
	// b - If the Entity is invulerable or not
	inline void setInvulerable(bool b) { _invulerable = b; }

protected:
	
	FloatingProgressBar _hpBar; // Health bar

	float _health; // Current health of the Entity
	float _maxHealth; // Max health this Entity can have

	bool _invulerable; // If this Entity can currently take damage
};

#endif
