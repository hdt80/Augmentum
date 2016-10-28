#ifndef _ENEMY_H
#define _ENEMY_H

#include "Vector2.h"
#include "Object.h"
#include "Unit.h"

class EnemyType {
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

	// Get the internal id to use
	// returns: _id
	int getId() { return _id; }

	// Get the display name of this EnemyType
	// returns: _name
	const std::string& getName() { return _name; }

	// Get the number of sides this EnemyType uses
	// returns: _sides
	int getSides() { return _sides; }

	// Get the default stats this EnemyType will have at level 1
	// returns: _defaultStats
	const Stats& getDefaultStats() { return _defaultStats; }

	// Get the stats at a certain level
	// returns: What the stats will be at level of this EnemyType
	Stats getStats(int level) { return _defaultStats + (_levelDiff * level); }

	// Static methods //////////////////////////////////////////////////////////
	
	// Get the EnemyType from the id
	// id - Id to get the EnemyType of
	// returns: The EnemyType with the matching id
	static EnemyType getById(int id);

	// Create a new EnemyType
	// id - ID to use internally
	// name - Display name to use
	// sides -  How many sides the this EnemyType uses
	// defStats - Default stats of the EnemyType
	// levelDiff - The stat different each level
	static void createEnemyType(int id, const std::string& name, int sides,
			Stats defStats, Stats levelDiff);

protected:
	int _id; // ID to use internally
	std::string _name; // Display name of the EnemyType
	int _sides; // How many sides this EnemyType has, sides determines the type
	Stats _defaultStats; // Default stats at level 1 the Enemy will have
	Stats _levelDiff; // Different in stats of each level

	// Static vars /////////////////////////////////////////////////////////////
	
	std::vector<EnemyType> _types; // _id to EnemyType
};

class Enemy : public Unit {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	Enemy();

	// Enemy ctor
	// map - Map to create this Enemy at
	// x - X coord of the map to create the Enemy at
	// y - Y coord of the map to create the Enemy at
	// type - EnemyType this is
	Enemy(Map* map, float x, float y, EnemyType type);

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

protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	sf::RectangleShape _hpBar;
};

#endif
