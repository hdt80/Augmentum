#ifndef _ENEMY_H
#define _ENEMY_H

#include "Vector2.h"
#include "Object.h"
#include "Unit.h"
#include "FloatingProgressBar.h"
#include "LuaConfigEntry.h"

class EnemyType : public LuaConfigEntry {
protected:
	// Ctor and dtor ///////////////////////////////////////////////////////////

	// EnemyType ctor
	// id - ID to use internally
	// name - Display name to use
	// sides -  How many sides the this EnemyType uses
	// defStats - Default stats of the EnemyType
	// levelDiff - The stat different each level
	EnemyType(int id, const std::string& name, int sides, Stats defStats,
			Stats levelDiff);
public:

	// Methods /////////////////////////////////////////////////////////////////
	
	// Inherited from LuaConfigEntry
	void readFromTable(const sol::table& table);

	// Get the internal id to use
	// returns: _id
	int getId() const { return _id; }

	// Set the internal id to use
	// i = new id to use
	void setId(int i) { _id = i; }

	// Get the display name of this EnemyType
	// returns: _name
	const std::string& getName() const { return _name; }

	// Get the number of sides this EnemyType uses
	// returns: _sides
	int getSides() const { return _sides; }

	// Get the default stats this EnemyType will have at level 1
	// returns: _defaultStats
	const Stats& getDefaultStats() const { return _defaultStats; }

	// Get the level diff Stats this EnemyType will use
	// returns: _levelDiff
	const Stats& getLevelDiffStats() const { return _levelDiff; }

	// Get the stats at a certain level
	// returns: What the stats will be at level of this EnemyType
	Stats getStats(int level) { return _defaultStats + (_levelDiff * level); }

	// Static methods //////////////////////////////////////////////////////////
	
	// Get the EnemyType from the id
	// id - Id to get the EnemyType of
	// returns: The EnemyType with the matching id
	static EnemyType* getById(int id);

	// Create a new EnemyType
	// id - requested id, not gaurenteed to give this id
	// name - Display name to use
	// sides -  How many sides the this EnemyType uses
	// defStats - Default stats of the EnemyType
	// levelDiff - The stat different each level
	// returns: The id used to store the created EnemyType
	static int createEnemyType(int id, const std::string& name, int sides,
			Stats defStats, Stats levelDiff);

	// Add a pre-existing EnemyType to the _types vector
	// type - Type to add
	// returns: The id used to store the added EnemyType
	static int addEnemyType(EnemyType& type);

	// Load an EnemyType from a lua file at the path
	//		The info should be subtabled in a subtable called Config{}
	// path - Path to the lua file, file extension included
	// returns: ID of the EnemyType created
	static int loadEnemyType(const std::string& path);

	// Get the default EnemyType returned when getById doesn't have that id
	// returns: _defaultType
	static EnemyType* getDefaultType();

	// See if an EnemyType is already in use
	// id - Id to check
	// returns: If _types contains id
	static bool idInUse(unsigned int id);

protected:
	int _id; // ID to use internally
	std::string _name; // Display name of the EnemyType
	int _sides; // How many sides this EnemyType has, sides determines the type
	Stats _defaultStats; // Default stats at level 1 the Enemy will have
	Stats _levelDiff; // Different in stats of each level

	// Static vars /////////////////////////////////////////////////////////////
	
	//static std::vector<EnemyType> _types; // _id to EnemyType

	static std::map<int, EnemyType> _types;

	static EnemyType _defaultType; // Default type to use
};

class Enemy : public Unit {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	Enemy();

	// Enemy ctor
	// map - Map to create this Enemy at
	// x - X coord of the map to create the Enemy at
	// y - Y coord of the map to create the Enemy at
	// size - Size in pixels of this Enemy
	// type - EnemyType this is
	Enemy(Map* map, float x, float y, int size, EnemyType type);

	// Enemy dtor
	virtual ~Enemy();

	// Methods /////////////////////////////////////////////////////////////////

	// Load the Lua script used by this Enemy
	void loadLua();

	// Update the enemy depending on its target, updating its coords
	// diff - Milliseconds since last update call
	virtual void update(int diff);

	// A simple target is just an (x, y) coord point. Because an Object
	// isn't just a coord point it isn't a simple target
	virtual bool isSimpleTarget() const { return false; }

	// Get the EnemyType this Enemy uses
	// returns: _enemyType
	const EnemyType& getEnemyType() { return _enemyType; }

protected:
	const EnemyType _enemyType; // Type of this Enemy
};

#endif
