#ifndef _LUA_SCRIPT_H
#define _LUA_SCRIPT_H

#include <string>
#include "sol/sol.hpp"
#include "Logger.h"

class LuaScript {
public:
	LuaScript(bool loadedClasses = true);

	bool isLoaded() { return _loaded; }
	void setLoaded(bool b) { _loaded = b; }

	// Load the file at that path. Any filetype can be used
	void loadScript(const std::string& path);
	// Print the table of the script loaded. 
	// Useful for debug when objects are nil
	void printTable();

	// Call a function loaded from a script
	template<typename... Args>
	void callFunction(const char* name, Args&&... args) {
		if (isLoaded()) {
			try {
				lua.get<sol::function>(name).template call<void>(args...);
			} catch (sol::error e) {
				CORE_ERROR("[Lua Script %x: %s] Error when calling \"%s\": %s",
					this, _name.c_str(), name, e.what());
			}
		}
	}

	sol::state lua;

protected:
	std::string _name; // File name that's loaded
	bool _loaded;

	void defineEnemy();
	void defineTower();
	void defineObject();
	void defineTarget();
	void defineMap();
	void defineStats();
	void definePerk();
};

#endif
