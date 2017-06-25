#include "LuaScript.h"

#include "LuaDefines.h"

#include "game/Object.h"
#include "game/Map.h"
#include "game/Target.h"
#include "game/Enemy.h"
#include "game/Perk.h"
#include "game/Stats.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

LuaScript::LuaScript(bool defineClasses) {
	_loaded = false;
	lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table,
		sol::lib::package, sol::lib::math, sol::lib::debug);

	if (defineClasses) {
		LuaDefines::defineClasses(lua);
	}
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void LuaScript::loadScript(const std::string& path) {
	try {
		_name = path;
		lua.script_file(path);
		setLoaded(true);
	} catch (sol::error e) {
		setLoaded(false);
		AG_ERROR("[Lua Script %x] Error when loading from \"%s\": %s",
			this, path.c_str(), e.what());
	}
}

void LuaScript::printTable() {
	auto iter = lua.begin();
	AG_INFO("[LuaScript %x] Print %s", this, _name.c_str());
	while (iter != lua.end()) {
		AG_INFO("%s", (*iter).first.as<std::string>().c_str());
		++iter;
	}
}
