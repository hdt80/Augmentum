#ifndef _OBJECT_H
#define _OBJECT_H

#include "Target.h"

#include "Box2D/Box2D.h"

#include "Stats.h"
#include "SkillTree.h"
#include "LuaScript.h"

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

	COUNT		= 0x0004 // How many types there are
};

class Object : public Target, public sf::Drawable, public sf::Transformable {
public:
	// A default constructor must be defined for Sol for some reason.
	// This constructor should never be used and is only for Sol
	Object();
	Object(Map* map, float x, float y, Stats s);
	virtual ~Object();

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
	
	// If that point is within our collision box
	// x - X coord of the map to check
	// y - Y coord of the map to check
	// returns: If the point (x, y) is within the boundbox of this Object
	bool contains(float x, float y) const;

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
	Stats getStatMod() const { return _stats; }
	Stats getStats() const { return _stats + _baseStats; }
    Stats getBaseStats() const { return _baseStats; };

	// Get specific stats
	int getSpeed() const { return _stats["speed"] + _baseStats["speed"]; }
	int getRange() const { return _stats["range"] + _baseStats["range"]; }
	float getFireRate() const { return _stats["fireRate"]
		+ _baseStats["fireRate"]; }
	float getDamage() const { return _stats["damage"] + _baseStats["damage"] ; }
	float getAccel() const { return _stats["accel"] + _baseStats["accel"] ; }
	float getProjSpeed() const { return _stats["projSpeed"]
		+ _baseStats["projSpeed"]; }

	// Stats setters
	void setRange(int r) { _stats["range"] = r; }
	void setFireRate(float r) { _stats["fireRate"] = r; }
	void setDamage(float d) { _stats["damage"] = d; }
	void setSpeed(int s) { _stats["speed"] = s; }
	void setAccel(float f) { _stats["accel"] = f; }
	void setProjSpeed(float f) { _stats["projSpeed"] = f; }

	// Perk methods ////////////////////////////////////////////////////////////
	
	virtual void addPerk(Perk* p);
	virtual void removePerk(Perk* p);
	bool hasPerk(std::string name) { return getPerk(name) != nullptr; }
	Perk* getPerk(int index) { return _perks[index]; }
	Perk* getPerk(std::string name); // nullptr if no Perk with that name

	// Other getters ///////////////////////////////////////////////////////////
	
	// Get what type of Object this is
	// returns: Enum of _objType
	ObjectType getObjectType() { return _objType; }

	// Set the ObjectType of this Object
	// type - Type to set the ObjectType to
	void setObjectType(ObjectType type);// { _objType = type; }

	// Get the Map this Object is on
	// returns: Pointer to the Map this Object is on
	Map* getMap() const { return _map; }

	// Get the perks attached to this Object
	// returns: Reference to the vector of perks this Object has
	std::vector<Perk*>& getPerks() { return _perks; }

	// Get where this Object is moving towards
	// returns: Pointer to the target of this Object
	Target* getTarget() const { return _target; }

	//
	Vector2 getDirection() const { return _direction; }

	// Get if this Object is to be removed in the next update of the Map
	// return: _toRemove
	bool isToRemove() const { return _toRemove; }

	// Get the SkillTree this Object uses
	// returns: Pointer to the SkillTree this Object uses
	SkillTree* getTree() const { return _tree; }

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
	void setSkillTree(SkillTree* tree);

	// Movement methods ////////////////////////////////////////////////////////
	
	// Set the velocity of this Object. The velocity won't be instantly set
	//		to this values, but accelerated to the vales
	// x - X velocity to accelerate to
	// y - Y velcotiy to accelerate to
	void setVelocity(float x, float y);

	// Update the position of this Object all all vars
	// x - X coord of the map to update to
	// y - Y coord of the map to update to
	void updatePosition(float x, float y);

	// Get the current linear velocity
	// returns: A Vector2 of the current linear velocity of this Object
	Vector2 getVelocity() { return Vector2(_b2Box->GetLinearVelocity().x,
			_b2Box->GetLinearVelocity().y); }

	virtual float getX() { return _b2Box->GetPosition().x; }
	virtual float getY() { return _b2Box->GetPosition().y; }

protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	sf::CircleShape _shape;

	b2Body* _b2Box;

	Map* _map; // Map this object is located on

	LuaScript _lua; // Script associated with this Object

	SkillTree* _tree; // Skill tree attached to this Object
	std::vector<Perk*> _perks; // Perks of this Object

	ObjectType _objType; // What type of Object this is
	int _attackerCount; // Number of Objects that have targetted us

	// Base stats are the stats that all perks base off of
	// Base stats only change on a level
    Stats _baseStats;
	// All calculations that affect other Object use this one
	Stats _stats;

	Target* _target; // Target the enemy is running to (can be coord or enemy)
	Vector2 _direction;

	bool _toRemove; // Is this object marked for removal?
};

#endif
