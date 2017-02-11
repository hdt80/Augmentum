#ifndef _ENEMY_TYPE_H
#define _ENEMY_TYPE_H

#include "LuaConfigEntry.h"
#include "Stats.h"

class EnemyType : public LuaConfigEntry {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// EnemyType ctor. Used to load the data from a lua table
	// table - Table to load all the values from. The table can have the
	//		follwing values. If any value is not specified the default value
	//		is loaded.
	//
	//		name: string - Display name shown to the player
	//		sides: int - Number of sides the EnemyType will have
	//		default_stats: stat table - Default stats the EnemyType will have at
	//			level 1
	//		level_diff_stats: stat table - Stats the EnemyType will gain each
	//			level
	EnemyType(const sol::table& table);

	// Nullary ctor required for Databases. The default values for strings are
	//		empty strings, 0 for ints, and Stats of 0.0f for stats
	EnemyType();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Inherited from LuaConfigEntry
	void readFromTable(const sol::table& table);

	// Value getters ///////////////////////////////////////////////////////////

	// Get the display name of the EnemyType
	// returns: _name
	inline const std::string& getName() const { return _name; }

	// Get the number of sides the EnemyType has
	// returns: _sides
	inline int getSides() const { return _sides; }

	// Get the default stats the EnemyType will have at level 1
	// returns: _defaultStats
	inline const Stats& getDefaultStats() const { return _defaultStats; }

	// Get the stats the EnemyType will gain for each level
	// returns: _levelDiff
	inline const Stats& getLevelDiffStats() const { return _levelDiff; }

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	std::string _name; // Display name of the EnemyType
	int _sides; // How many sides this EnemyType has, sides determines the type
	Stats _defaultStats; // Default stats at level 1 the Enemy will have
	Stats _levelDiff; // Different in stats of each level
};

#endif
