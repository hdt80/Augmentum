#ifndef _EVENTABLE_H
#define _EVENTABLE_H

class Object;
class Unit;

class Eventable {
public:
	// Ctor and dtor

	// Dtor for Eventable
	virtual ~Eventable() {};

	// Multiuse events /////////////////////////////////////////////////////////

	// Occurs when an update is called
	// diff - Microseconds to simulate for
	virtual void onUpdate(int diff) {}

	// Perk events /////////////////////////////////////////////////////////////

	// Occurs when a Perk is applied to an Object
	// o - Object applied to
	virtual void onApply(Object* o) {}

	// Object events ///////////////////////////////////////////////////////////
	
	// Occurs when an Object collides with another. Usually two events are
	//		called with eacher other as they collide with each other
	// o - Object collided with
	virtual void onCollision(Object* o) {}

	// Occurs when an Object shoots at another
	// target - Object being shot at
	virtual void onShoot(Object* target) {}

	// Occurs when a move occurs
	// diff - Microseconds since the last move
	virtual void onMove(int diff) {}

	// Occurs when an Object deals damage to another Object
	// dmg - Amount of damage dealt. Negative damage means a heal
	// hit - Object hit
	virtual void onDamageDealt(int dmg, Object* hit) {}

	// Occurs when an Object takes damage from another Object
	// dmg - Amount of damage taken. Negative damage means a heal
	// attacker - Object that dealt the damage
	virtual void onDamageTaken(int dmg, Object* attacker) {}

	// Occurs when an Object is killed
	virtual void onDeath() {}
	
	// Unit events /////////////////////////////////////////////////////////////

	// Occurs when a Unit's level changes
	virtual void onLevelUp() {}

	// Occurs when a Unit kills another Unit
	// killed - Unit killed
	virtual void onUnitKill(Unit* killed) {}

protected:
};

#endif
