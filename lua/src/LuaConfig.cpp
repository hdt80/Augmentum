#include "lua/LuaConfig.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

LuaConfig::LuaConfig()
	: _loaded(false) {

}

LuaConfig::~LuaConfig() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void LuaConfig::openConfigFile(const std::string& path) {
	try {
		_name = path;
		_lua.script_file(path);
		setLoaded(true);

		_configTable = _lua.get<sol::table>("config");
	} catch (sol::error e) {
		setLoaded(false);
		AG_ERROR("[Lua Config %x] Error when loading from \"%s\": %s",
			this, path.c_str(), e.what());
	}
}

////////////////////////////////////////////////////////////////////////////////
// Reading methods
////////////////////////////////////////////////////////////////////////////////

float LuaConfig::readFloat(const std::string& key) const {
	try {
		return _configTable.get<float>(key);
	} catch (sol::error e) {
		AG_ERROR("[Lua Config %x] Error when reading \'%s\' from \"%s\": %s",
			this, key.c_str(), _name.c_str(), e.what());
		return -1;
	}
}

int LuaConfig::readInt(const std::string& key) const {
	try {
		return _configTable.get<int>(key);
	} catch (sol::error e) {
		AG_ERROR("[Lua Config %x] Error when reading \'%s\' from \"%s\": %s",
			this, key.c_str(), _name.c_str(), e.what());
		return -1;
	}
}

bool LuaConfig::readBool(const std::string& key) const {
	try {
		return _configTable.get<bool>(key);
	} catch (sol::error e) {
		AG_ERROR("[Lua Config %x] Error when reading \'%s\' from \"%s\": %s",
			this, key.c_str(), _name.c_str(), e.what());
		return false;
	}
}

std::string LuaConfig::readString(const std::string& key) const {
	try {
		return _configTable.get<std::string>(key);
	} catch (sol::error e) {
		AG_ERROR("[Lua Config %x] Error when reading \'%s\' from \"%s\": %s",
			this, key.c_str(), _name.c_str(), e.what());
		return "";
	}
}

////////////////////////////////////////////////////////////////////////////////
// Writing methods
////////////////////////////////////////////////////////////////////////////////

void LuaConfig::writeFloat(const std::string& key, const float& value) {
	_lua[key] = value;
}

void LuaConfig::writeInt(const std::string& key, const int& value) {
	_lua[key] = value;
}

void LuaConfig::writeBool(const std::string& key, const bool& value) {
	_lua[key] = value;
}

void LuaConfig::writeString(const std::string& key, const std::string& value) {
	_lua[key] = value;
}
