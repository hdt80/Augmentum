#ifndef _LUA_CONFIG_ENTRY_H
#define _LUA_CONFIG_ENTRY_H

#include "LuaConfig.h"
#include <string>

class LuaConfigEntry {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// LuaConfigEntry ctor
	// name - Sub table in the config file to load the values from
	LuaConfigEntry(const std::string& name)
		: _name(name) {}

	// LuaConfigEntry dtor
	virtual ~LuaConfigEntry() {}

	// Methods /////////////////////////////////////////////////////////////////

	// Load all the value from a sol::table, the table should have the same
	//		name as _name
	// table - Table to load the values from
	virtual void readFromTable(const sol::table& table) = 0;

	// Load all the values from a LuaConfig into the object
	// config - LuaConfig to read from
	virtual void readFromConfig(const LuaConfig& config);

	// Load all the values from a file
	virtual void readFromFile(const std::string& path);

	// Name getter /////////////////////////////////////////////////////////////
	
	// Get the name of the sub table all the values are located at
	// returns: A const reference to _name
	inline const std::string& getName() const { return _name; }

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	std::string _name; // Name of the sub table all the info is located at
};

#endif
