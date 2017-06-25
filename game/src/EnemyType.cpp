#include "game/EnemyType.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

EnemyType::EnemyType(const sol::table& table)
	: LuaConfigEntry("EnemyType") {

	readFromTable(table);
}

EnemyType::EnemyType()
	: LuaConfigEntry("EnemyType"),
		_name(""), _sides(0), _defaultStats(0.0f), _levelDiff(0.0f) {
		
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void EnemyType::readFromTable(const sol::table& table) {
	_name = table.get<std::string>("name");
	_sides = table.get<int>("sides");

	// Temp stats to load from the config
	Stats defStats;
	Stats lvlDiff;

	defStats.readFromTable(table["default_stats"]);
	lvlDiff.readFromTable(table["level_diff_stats"]);

	_defaultStats = defStats;
	_levelDiff = lvlDiff;
}
