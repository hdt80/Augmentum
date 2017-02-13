#ifndef _LUA_CONFIG
#define _LUA_CONFIG

#include <string>

#include "sol/sol.hpp"

class LuaConfig {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////

	// LuaConfig ctor
	LuaConfig();

	// LuaConfig dtor
	~LuaConfig();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Load all the config values into this object
	// path - File path to load. Include the extension
	void openConfigFile(const std::string& path);

	// Check if the config file is loaded
	// returns: _loaded
	inline bool isLoaded() const { return _loaded; }

	// Set of the config file is loaded
	// b - Is the file loaded or not
	inline void setLoaded(bool b) { _loaded = b; }

	// Get the name of the file loaded
	// returns: _name
	inline const std::string& getName() const { return _name; }

	// Get the config table used in LuaConfig
	// returns: A reference to _configTable
	inline const sol::table& getConfigTable() const { return _configTable; }

	// Reading methods /////////////////////////////////////////////////////////
	
	// Read a float value from the file
	// key - Key to read
	// returns: The value matching the key, or -1 if no key matches
	float readFloat(const std::string& key) const;

	// Read an int value from the file
	// key - Key to read
	// returns: The value matching the key, or -1 if no key matches
	int readInt(const std::string& key) const;

	// Read a bool value from the file
	// key - Key to read
	// returns: The value matching the key, or false if no key matches
	bool readBool(const std::string& key) const;

	// Read a string value from the file
	// key - Key to read
	// returns: The value matching the key, or an empty string if no match
	std::string readString(const std::string& key) const;

	// Writing methods /////////////////////////////////////////////////////////

	// Write a float to the config. This will override the existing value
	// key - What name to store the value as
	// value - Value to write to the file
	void writeFloat(const std::string& key, const float& value);

	// Write an int to the config. This will override the existing value
	// key - What name to store the value as
	// value - Value to write to the file
	void writeInt(const std::string& key, const int& value);

	// Write a string to the config. This will override the existing value
	// key - What name to store the value as
	// value - Value to write to the file
	void writeString(const std::string& key, const std::string& value);

	// Write a bool to the config. This will override the existing value
	// key - What name to store the value as
	// value - Value to write to the file
	void writeBool(const std::string& key, const bool& value);

protected:

	// Is this config file loaded
	bool _loaded;

	// Lua that's been loaded
	sol::state _lua;

	// The config will only read values in the config{} table from the file
	sol::table _configTable;

	// Name of the loaded lua file
	std::string _name;
};

#endif
