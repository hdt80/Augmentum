#include "LuaConfigEntry.h"
#include "Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void LuaConfigEntry::readFromFile(const std::string& path) {
	LuaConfig config;
	config.openConfigFile(path);

	if (!config.isLoaded()) {
		CORE_ERROR("[LuaConfigEntry %x] Failed to load \"%s\"", this,
			path.c_str());
	}

	readFromConfig(config);
}

void LuaConfigEntry::readFromConfig(const LuaConfig& config) {
	// This only loads the first one
	readFromTable(config.getConfigTable()[getName()]);
}

sf::Color LuaConfigEntry::getSfColor(const sol::table& table) const {
	sf::Color color;

	if (!table.valid()) {
		CORE_ERROR("Passed table is invalid. Returning default sf::Color");
		return color;
	}

	// Default to black
	color.r = table.get_or("R", 0);
	color.g = table.get_or("G", 0);
	color.b = table.get_or("B", 0);
	color.a = table.get_or("A", 255);

	return color;
}
