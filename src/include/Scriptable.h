#ifndef _SCRIPTABLE_H
#define _SCRIPTABLE_H

#include "LuaScript.h"

#include <string>

class Object;
class Unit;
class Projectile;
class Entity;

class Scriptable {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////

	// Dtor for Eventable
	virtual ~Scriptable();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Load a file as a lua script
	// filepath - Path relative from the current working directory to load
	//		the lua script from. The file does not have to be a .lua file, any
	//		file will work as long as it can be loaded as a lua script. The
	//		file extension should be included as well.
	// returns: If the lua script was loaded properly
	bool loadFile(const std::string& filepath);
	
	// Events //////////////////////////////////////////////////////////////////

	// Occurs when an update is called
	// diff - Microseconds to simulate for
	virtual void onUpdate(int diff);

	// Occurs when a Perk is applied to a Unit
	// unit - Unit the Perk is being applied to
	virtual void onApply(Unit* unit);
	
	// Occurs when an Object collides with another. Usually two events are
	//		called with eacher other as they collide with each other.
	// o - Object the Objected collided with
	virtual void onCollision(Object* o);

	// Occurs when a Projectile collides with this Object
	// p - Projectile that his us
	virtual void onProjectileHit(Projectile* p);

	// Occurs when a Unit fires a shot at a point
	// x - X component of the coord the Unit shot at
	// y - Y component of the coord the Unit shot at
	virtual void onShoot(float x, float y);

	// Occurs when a move occurs
	// diff - Microseconds since the last move
	virtual void onMove(int diff);

	// Occurs when a Unit deals damage to an Entity
	// dmg - Damage dealt to the Entity. Negative damage indicates a heal
	//		rather than damage dealt
	// hit - Entity that was recieving the damage
	virtual void onDamageDealt(int dmg, Entity* hit);

	// Occurs when an Entity takes damage from a Unit
	// dmg - Damage taken from the Unit. Negative damage indicates a heal
	//		rather than damage dealt to this Entity
	// attacker - Unit that dealt the damage to the Entity
	virtual void onDamageTaken(int dmg, Unit* attacker);

	// Occurs when an Entity dies
	virtual void onDeath();

	// Occurs when the Entity is killed by a Unit. This is different from
	//		onDeath as onDeath occurs whenever an Object dies. onDeath is
	//		called when an Entity is killed, but not from onKilled
	// killer - Unit that killed the Entity
	virtual void onKilled(Unit* killer);

	// Occurs when a Unit's level changes
	// newLevel - New level of the Unit
	virtual void onLevelUp(int newLevel);

	// Occurs when a Unit kills an Entity
	// killed - Entity killed by the Unit
	virtual void onEntityKilled(Entity* killed);

protected:

	// Script used when calling all the events
	LuaScript _script;
};

#endif
