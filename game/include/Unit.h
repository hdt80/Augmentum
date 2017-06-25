#pragma once

#include "game/Entity.h"
#include "game/Cooldown.h"
#include "game/SkillTree.h"

// A Unit has all the properties of an Entity, but also has stats and perks 
// that change how the Unit functions. A Unit takes and deals damage, typically
// by shooting Projectiles. Units can shoot Projectiles, and have a reload
// cooldown between each shot.
// Examples: Ships
class Unit : public Entity {
public:
	// ctor and dtor ///////////////////////////////////////////////////////////

	// Unit ctor
	// map - Map this Unit is a part of
	// x - X coord of the world to create this Unit at
	// y - Y coord of the world to create this Unit at 
	// s - Stats this Unit will use
	// lvlDiff - Stats to gain each level
	// size - Size in pixels of this Unit
	// sides - How many sides this Unit has
	// c - Color to draw this Unit
	Unit(Map* map, float x, float y, Stats s, Stats lvlDiff,
		int size, int sides, sf::Color c);

	// Unit dtor
	virtual ~Unit();

	// Methods /////////////////////////////////////////////////////////////////

	// Simulate the update for an amount of time
	// diff - Microseconds to simulate the Unit for
	void update(int diff);

	// Events //////////////////////////////////////////////////////////////////
	
	// Occurs when a Projectile collides with this Object
	// p - Projectile that his us
	void onProjectileHit(Projectile* p);

	// Occurs when a Unit kills an Entity
	// killed - Entity killed by the Unit
	void onEntityKilled(Entity* killed);

	// Occurs when a Unit's level changes
	// newLevel - New level of the Unit
	void onLevelUp();

	// Shooting methods ////////////////////////////////////////////////////////
	
	// Check if this Unit can shoot
	// returns: If the _reload Cooldown is completed
	inline bool canShoot() const { return _reload.done(); }

	// Shoot towards a point
	// x - X coord of the Map to shoot at
	// y - Y coord of the Map to shoot at
	virtual void shoot(float x, float y);

	// Shoot at a Target
	// target - Target to shoot towards
	inline void shoot(Target* target) { shoot(target->getX(), target->getY()); }

	// Position methods ////////////////////////////////////////////////////////

	// Set the velocity of the Unit. The velocity will slowly approach the
	//		values of (x, y) over time.
	// x - X component of the velocity in Map units
	// y - Y component of the velocity in Map units
	virtual void setVelocity(float x, float y);

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

	// Skill tree methods //////////////////////////////////////////////////////

	// Set the SkillTree
	// tree - SkillTree to copy
	void setSkillTree(SkillTree* tree);

	// Get the SkillTree this Object uses
	// returns: Pointer to the SkillTree this Object uses
	inline SkillTree* getTree() const { return _tree; }

	// Stat methods ////////////////////////////////////////////////////////////
	
	// Apply new stats to the object
	// If it's relative change stats relative to current stats
	void applyStat(Stats s);
    void setStats(Stats s, bool relative = true);

	// Stats getters
	inline const Stats& getStatMod() const { return _statMods; }
	inline Stats getStats() const { return _statMods + _baseStats; }
    inline const Stats& getBaseStats() const { return _baseStats; };

	// Get the value of a specific stat
	// name - Name of the stat to get
	// returns: The value of the stat with the matching name, or 0 if that name
	//		couldn't be found.
	virtual float getStat(const std::string& name) const;

	// Set the value of a stat. If the stat does not exist it will be created
	// name - Name of the stat to set
	// value - Value to set the stat to
	void setStat(const std::string& name, float value);

	// Specific stat getters ///////////////////////////////////////////////////
	
	// Getters
	inline float getSpeed() const { return getStat("speed"); }
	inline float getRange() const { return getStat("range"); }
	inline float getFireRate() const { return getStat("fireRate"); }
	inline float getDamage() const { return getStat("damage"); }
	inline float getAccel() const { return getStat("accel"); }
	inline float getProjSpeed() const { return getStat("projSpeed"); }

	// Setters
	inline void setRange(int r) { setStat("range", r); }
	inline void setFireRate(float r) { setStat("fireRate", r); }
	inline void setDamage(float d) { setStat("damage", d); }
	inline void setSpeed(int s) { setStat("speed", s); }
	inline void setAccel(float f) { setStat("accel", f); }
	inline void setProjSpeed(float f) { setStat("projSpeed", f); }

	// Perk methods ////////////////////////////////////////////////////////////

	// Get the Perks currently acting on this Unit
	// returns: _perks
	inline const std::vector<Perk*>& getPerks() const { return _perks; }

	// Get how many Perks are currently acting on this Unit
	// returns: _perks.size()
	unsigned int perkCount() const { return _perks.size(); }

	// Add a new Perk acting on this Unit
	// p - Perk to begin acting on this Unit
	virtual void addPerk(Perk* p);

	// Remove a Perk from acting on this Unit
	// p - Perk to remove
	virtual void removePerk(Perk* p);

	// Check if the Unit has a Perk with a certain name
	// name - Name of the Perk to check for
	// returns: If _perks contains a Perk with a name of name
	bool hasPerk(const std::string& name) { return getPerk(name) != nullptr; }

	// Get a Perk based on the name
	// name - Name of the perk
	// returns: The first Perk matching the name, or nullptr if no Perk matches
	//		the name supplied
	Perk* getPerk(const std::string& name) const;

protected:
	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	// Cooldown to track when a Unit can fire another Projectile. When reload
	// is at 0 then the Unit can fire again. Trying to shoot while reloading
	// will not reset the reload cooldown.
	Cooldown _reload;

	// How much the stats will grow each level. These Stats are provided
	// in absolute values. To get the stats provided by the level diff
	// multiply a Unit's level by _levelDiff
	Stats _levelDiff;
	// Base stats that this Unit starts out with. All percent increases of
	// stats are calculated from the base + the level diff
	Stats _baseStats;
	// Stats that are provided from Perks or other sources that temporarily
	// change a Unit's stats
	Stats _statMods;

	// Perks currently attached to this Unit
	std::vector<Perk*> _perks;

	float _exp; // Current experience of this Unit
	int _prevLevel; // Used to check if the Unit has gone up a level

	SkillTree* _tree; // Skill tree attached to this Unit
};
