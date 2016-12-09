#ifndef _OBJECT_H
#define _OBJECT_H

#include "Target.h"

#include "Box2D/Box2D.h"

#include "Stats.h"
#include "SkillTree.h"
#include "LuaScript.h"
#include "Eventable.h"

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Map;
class Perk;

enum ObjectType {
	DEFAULT		= 0x0001,
	BOUNDARY	= 0x0002,
	FRIENDLY	= 0x0004,
	ENEMY		= 0x0008,
	PROJECTILE  = 0x0020,

	COUNT		= 0x0005 // How many types there are
};

class Object : public Eventable, public Target,
	public sf::Drawable, public sf::Transformable {
public:

	// Ctor and dtor ///////////////////////////////////////////////////////////

	// A default constructor must be defined for Sol for some reason
	// This constructor should never be used and is only for Sol
	Object();

	// Object ctor
	// map - Map this Object is on
	// x - X position of the map to create the Object at
	// y - Y position of the map to create the Object at
	// s - Stats this Object spawns with
	// size - Size in pixels of this Object
	Object(Map* map, float x, float y, Stats s, int size);

	// Object dtor
	virtual ~Object();

	// Methods /////////////////////////////////////////////////////////////////

	// If Object* o collides with us
	bool collidesWith(Object* o) const;

	// Load the Lua file and define all helper Lua methods
	virtual void loadLua();

	// Events //////////////////////////////////////////////////////////////////
	
	// Occurs when this Object collides with another
	// o - Object this Object collided with
	virtual void onCollision(Object* o);

	// Occurs every update
	// diff - Microseconds that happened for the update
	virtual void onUpdate(int diff);

	// Occurs when this Object moves
	// diff - Microseconds that happened for the move
	virtual void onMove(int diff);

	// Occurs when this Object fires a Projectile at another
	// target - Object this Object shot at
	//		the target will be nullptr if the Projectile is not targeted
	virtual void onShoot(Object* target);
	
	// Occurs when this Object took damage
	// dmg - How much damage was taken
	// attacker - Which Object was responsible for the damage taken
	virtual void onDamageTaken(int dmg, Object* attacker);

	// Occurs when damage was dealt to another Object
	// dmg - How much damage was applied
	// hit - What Object was hit
	virtual void onDamageDealt(int dmg, Object* hit);

	// Occurs when this Object dies (health = 0);
	virtual void onDeath();

	// Update methods //////////////////////////////////////////////////////////

	// Moves the object depending on it's target, updating it's position
	// diff - Milliseconds the object is supposed to move for
	virtual void move(int diff);

	// Update the enemy depending on its target, updating its coords
	// diff - Milliseconds since last update call
	virtual void update(int diff);

	// A simple target is just an (x, y) coord point. Because an Object
	// isn't just a coord point it isn't a simple target
	virtual bool isSimpleTarget() const { return false; }

	// Stats ///////////////////////////////////////////////////////////////////
	
	// Apply new stats to the object
	// If it's relative change stats relative to current stats
	void applyStat(Stats s);
    void setStats(Stats s, bool relative = true);

	// Stats getters
	inline const Stats& getStatMod() const { return _stats; }
	inline Stats getStats() const { return _stats + _baseStats; }
    inline const Stats& getBaseStats() const { return _baseStats; };

	// Get a stat
	// name - Name of the stat to get
	// returns: The value of the stat with the matching name
	virtual float getStat(const std::string& name) const;

	// Set the value of a stat
	// name - Name of the stat to set
	// value - Value to set the stat to
	void setStat(const std::string& name, float value);

	// Specific stat getters ///////////////////////////////////////////////////
	
	// Getters
	float getSpeed() const { return getStat("speed"); }
	float getRange() const { return getStat("range"); }
	float getFireRate() const { return getStat("fireRate"); }
	float getDamage() const { return getStat("damage"); }
	float getAccel() const { return getStat("accel"); }
	float getProjSpeed() const { return getStat("projSpeed"); }

	// Setters
	void setRange(int r) { setStat("range", r); }
	void setFireRate(float r) { setStat("fireRate",  r); }
	void setDamage(float d) { setStat("damage", d); }
	void setSpeed(int s) { setStat("speed", s); }
	void setAccel(float f) { setStat("accel", f); }
	void setProjSpeed(float f) { setStat("projSpeed", f); }

	// Perk methods ////////////////////////////////////////////////////////////
	
	virtual void addPerk(Perk* p);
	virtual void removePerk(Perk* p);
	bool hasPerk(std::string name) { return getPerk(name) != nullptr; }
	Perk* getPerk(int index) { return _perks[index]; }
	Perk* getPerk(std::string name); // nullptr if no Perk with that name

	// Object type getter and setter ///////////////////////////////////////////
	
	// Get what type of Object this is
	// returns: Enum of _objType
	inline int getObjectType() const { return _objType; }

	// Set the ObjectType of this Object
	// type - Type to set the ObjectType to
	void setObjectType(int type);

	// Add an object type option to the _objType flag
	// type - Object type option to set
	void addObjectTypeOption(int type);

	// Query if this Object has a specific option set
	// type - Type to check for
	// returns: If _objType contains the flag
	bool isObjectTypeOptionSet(int type);

	// Other getters ///////////////////////////////////////////////////////////
	
	// Get the Map this Object is on
	// returns: Pointer to the Map this Object is on
	inline Map* getMap() const { return _map; }

	// Get the size of this Object
	// returns: _size
	inline int getSize() const { return _size; }

	// Get the perks attached to this Object
	// returns: Reference to the vector of perks this Object has
	std::vector<Perk*>& getPerks() { return _perks; }

	// Get where this Object is moving towards
	// returns: Pointer to the target of this Object
	inline Target* getTarget() const { return _target; }

	// Get the direction this Object is heading towards
	// returns: _direction
	inline const Vector2& getDirection() const { return _direction; }

	// Get if this Object is to be removed in the next update of the Map
	// return: _toRemove
	inline bool isToRemove() const { return _toRemove; }

	// Utility getters /////////////////////////////////////////////////////////
	
	// Get how many perks this Object is that are active
	// returns: Size of _perks vector
	unsigned int perkCount() const { return _perks.size(); }

	// Attacker changes ////////////////////////////////////////////////////////
	
	void setAttackerCount(int c) { _attackerCount = c; }
	void incAttackerCount() { ++_attackerCount; }
	void decAttackerCount() { --_attackerCount; }

	// Get how many Objects have a pointer to this Object while targetting
	// returns: _attackerCount
	int getAttackerCount() const { return _attackerCount; }

	// Other setters ///////////////////////////////////////////////////////////
	
	void setTarget(Target* t);
	void setToRemove(bool b) { _toRemove = b; }

	// Set the size of this Object
	// size - New size to use
	void setSize(int size) { _size = size; }

	// Movement methods ////////////////////////////////////////////////////////
	
	// Set the velocity of this Object. The velocity won't be instantly set
	//		to this values, but accelerated to the vales
	// x - X velocity to accelerate to
	// y - Y velcotiy to accelerate to
	void setVelocity(float x, float y);

	// Update the position of this Object all all vars
	// x - X coord of the map to update to
	// y - Y coord of the map to update to
	virtual void updatePosition(float x, float y);

	// Get the current linear velocity
	// returns: A Vector2 of the current linear velocity of this Object
	Vector2 getVelocity() { return Vector2(_b2Box->GetLinearVelocity().x,
			_b2Box->GetLinearVelocity().y); }

	// Get the world position of this Object
	// returns: the X coord of the world position
	virtual float getX() const { return _b2Box->GetPosition().x; }

	// Get the world position of this Object
	// returns: the Y coord of the world position
	virtual float getY() const { return _b2Box->GetPosition().y; }

	// Collision methods ///////////////////////////////////////////////////////
	
	// Add a new Object to the collision
	// o - Object to add
	void addCollision(Object* o);

	// Remove an Object from the collisions
	// o - Object to remove
	void removeCollision(Object* o);

	// Clear all collisions
	void clearCollisions();

	// See if an Object is collided with an Object
	// o - Object to check
	// returns: If o is found in _collisions
	bool hasCollision(Object* o) const;

	// If that point is within our collision box
	// x - X coord of the map to check
	// y - Y coord of the map to check
	// returns: If the point (x, y) is within the boundbox of this Object
	bool contains(float x, float y) const;

protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	std::vector<Object*> _collisions; // Vector of collisions

	sf::CircleShape _shape; // Shape to draw the OBject with

	b2Body* _b2Box; // Collision box used in Box2D

	Map* _map; // Map this object is located on

	LuaScript _lua; // Script associated with this Object

	std::vector<Perk*> _perks; // Perks of this Object

	int _objType; // What type of Object this is

	int _attackerCount; // Number of Objects that have targetted us

	int _size; // Radius in pixels of this Object

	// Base stats are the stats that all perks base off of
	// Base stats only change on a level
    Stats _baseStats;
	// All calculations that affect other Object use this one
	Stats _stats;

	Target* _target; // Target the enemy is running to (can be coord or enemy)
	Vector2 _direction; // Direction this Object is moving in

	bool _toRemove; // Is this object marked for removal?
};

#endif
