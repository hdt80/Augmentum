#ifndef _OBJECT_H
#define _OBJECT_H

#include "Target.h"

#include <box2d/Box2d.h>

#include "Stats.h"
#include "SkillTree.h"
#include "LuaScript.h"
#include "BoundBox.h"

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Map;
class Perk;

class Object : public Target, public b2ContactListener, 
		public sf::Drawable, public sf::Transformable {
public:
	// A default constructor must be defined for Sol for some reason.
	// This constructor should never be used and is only for Sol
	Object();
	Object(Map* map, float x, float y, Stats s);
	virtual ~Object();

	// If Object* o collides with us
	bool collidesWith(Object* o) const;
	// Methods inherited from b2ContactListener
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2Manifold* newManifold);

	// Load the Lua file and define all helper Lua methods
	virtual void loadLua();

	// Events
	virtual void onCollision(Object* o);
	virtual void onUpdate(int diff);
	virtual void onMove(int diff);
	virtual void onShoot(Object* target);
	virtual void onDamageTaken(int dmg, Object* attacker);
	virtual void onDamageDealt(int dmg, Object* hit);
	virtual void onDeath();

	// If that point is within our collision box
	bool contains(float x, float y) const;
	bool intersectsWith(BoundBox* b) const;

	// Get the collision box of this Object
	virtual sf::FloatRect getCollisionBox() const { return _shape.getGlobalBounds(); }

	// Moves the object depending on it's target, updating it's position
	// diff - Milliseconds the object is supposed to move for
	virtual void move(int diff);

	// Update the enemy depending on its target, updating its coords
	// diff - Milliseconds since last update call
	virtual void update(int diff);

	// A simple target is just an (x, y) coord point. Because an Object
	// isn't just a coord point it isn't a simple target
	virtual bool isSimpleTarget() const { return false; }

	////////////////////////////////////////////////////////////////////////////
	// Stats
	////////////////////////////////////////////////////////////////////////////
	
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
	float getFireRate() const { return _stats["fireRate"] + _baseStats["fireRate"]; }
	float getDamage() const { return _stats["damage"] + _baseStats["damage"] ; }
	float getAccel() const { return _stats["accel"] + _baseStats["accel"] ; }
	float getProjSpeed() const { return _stats["projSpeed"] + _baseStats["projSpeed"]; }

	// Stats setters
	void setRange(int r) { _stats["range"] = r; }
	void setFireRate(float r) { _stats["fireRate"] = r; }
	void setDamage(float d) { _stats["damage"] = d; }
	void setSpeed(int s) { _stats["speed"] = s; }
	void setAccel(float f) { _stats["accel"] = f; }
	void setProjSpeed(float f) { _stats["projSpeed"] = f; }

	////////////////////////////////////////////////////////////////////////////
	// Perk methods
	////////////////////////////////////////////////////////////////////////////
	virtual void addPerk(Perk* p);
	virtual void removePerk(Perk* p);
	bool hasPerk(std::string name) { return getPerk(name) != nullptr; }
	Perk* getPerk(int index) { return _perks[index]; }
	Perk* getPerk(std::string name); // nullptr if no Perk with that name

	////////////////////////////////////////////////////////////////////////////
	// Other getters
	////////////////////////////////////////////////////////////////////////////
	Map* getMap() const { return _map; }
	std::vector<Perk*>& getPerks() { return _perks; }
	Target* getTarget() const { return _target; }
	Vector2 getDirection() const { return _direction; }
	bool isToRemove() const { return _toRemove; }
	SkillTree* getTree() const { return _tree; }
	int getAttackerCount() const { return _attackerCount; }

	////////////////////////////////////////////////////////////////////////////
	// Utility getters
	////////////////////////////////////////////////////////////////////////////
	unsigned int perkCount() const { return _perks.size(); }

	////////////////////////////////////////////////////////////////////////////
	// Attacker changes
	////////////////////////////////////////////////////////////////////////////
	void setAttackerCount(int c) { _attackerCount = c; }
	void incAttackerCount() { ++_attackerCount; }
	void decAttackerCount() { --_attackerCount; }

	////////////////////////////////////////////////////////////////////////////
	// Other setters
	////////////////////////////////////////////////////////////////////////////
	void setTarget(Target* t);
	void setToRemove(bool b) { _toRemove = b; }
	void setSkillTree(SkillTree* tree);

	////////////////////////////////////////////////////////////////////////////
	// Movement methods
	////////////////////////////////////////////////////////////////////////////
	void setVelocity(float x, float y);
	Vector2 getVelocity() { return Vector2(_b2Box->GetLinearVelocity().x, _b2Box->GetLinearVelocity().y); }
	virtual float getX() { return _b2Box->GetPosition().x; }
	virtual float getY() { return _b2Box->GetPosition().y; }

	////////////////////////////////////////////////////////////////////////////
	// Bound box
	////////////////////////////////////////////////////////////////////////////
	BoundBox* getBoundBox() const { return _boundBox; }
	void setBoundBox(BoundBox* box) { _boundBox = box; }

protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	sf::CircleShape _shape;

	b2Body* _b2Box;

	BoundBox* _boundBox; // Bounding box of this Object

	Map* _map; // Map this object is located on

	LuaScript _lua; // Script associated with this Object

	SkillTree* _tree; // Skill tree attached to this Object
	std::vector<Perk*> _perks;

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
