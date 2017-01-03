#ifndef _LUA_SCRIPT_H
#define _LUA_SCRIPT_H

#include <string>
#include "sol/sol.hpp"
#include "Logger.h"

class LuaScript {
public:

	// Ctor and dtor ///////////////////////////////////////////////////////////

	// LuaScript ctor
	// loadedClasses - Load the classes
	LuaScript(bool loadedClasses = true);

	// Methods /////////////////////////////////////////////////////////////////

	// Check if a script has been loaded
	// returns: _loaded
	inline bool isLoaded() { return _loaded; }

	// Set if this script is loaded
	// b - Loaded or not
	inline void setLoaded(bool b) { _loaded = b; }

	// Load the file at that path. Any filetype can be used
	// path - Path relative to the running directory of the program
	void loadScript(const std::string& path);

	// Print the table of the script loaded.
	// Useful for debug when objects are nil
	void printTable();

	// Call a function loaded from a script
	// name - Name of the function to call
	// args - Varadic list of args to call when calling the function named name
	template<typename... Args>
	void callFunction(const char* name, Args&&... args) {
		if (isLoaded()) {
			try {
				lua.get<sol::function>(name).template call<void>(args...);
			} catch (const sol::error& e) {
				CORE_ERROR("[Lua Script %x: %s] Error when calling \"%s\": %s",
					this, _name.c_str(), name, e.what());
			}
		}
	}

	// Static methods //////////////////////////////////////////////////////////
	
	// Define the objects used in scripting
	static void defineClasses(sol::state& lua);

	sol::state lua;

protected:

	// Vars ////////////////////////////////////////////////////////////////////
	
	std::string _name; // File name that's loaded
	bool _loaded; // Has this script been loaded?

	// Static methods //////////////////////////////////////////////////////////

	static void defineEnemy(sol::state& lua);
	static void defineObject(sol::state& lua);
	static void defineTarget(sol::state& lua);
	static void defineMap(sol::state& lua);
	static void defineStats(sol::state& lua);
	static void definePerk(sol::state& lua);
};

#endif
