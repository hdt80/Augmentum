#include "LuaDefines.h"

#include "game/Stats.h"

namespace LuaDefines {
	void defineStats(sol::state& lua) {
		lua.new_usertype<Stats>(
			"Stats", sol::constructors<
				sol::types<bool>, sol::types<float>>(),
			"print", &Stats::print,
			"addStat", &Stats::addStat,
			"setStat", &Stats::setStat,
			"hasStat", &Stats::hasStat,
			"getStat", &Stats::getStat,
			"isPercentage", &Stats::isPercentage
		);
	}
};
