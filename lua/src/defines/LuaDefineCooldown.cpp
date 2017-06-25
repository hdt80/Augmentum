#include "LuaDefines.h"

#include "game/Cooldown.h"

namespace LuaDefines {
	void defineCooldown(sol::state& lua) {
		lua.new_usertype<Cooldown> (
			"Cooldown", sol::constructors<sol::types<int>>(),
			"update", &Cooldown::update,
			"start", &Cooldown::start,
			"getRatioDone", &Cooldown::getRatioDone,
			"addTime", &Cooldown::addTime,
			"getTimeLeft", &Cooldown::getTimeLeft,
			"done", &Cooldown::done,
			"getMaxCooldown", &Cooldown::getMaxCooldown,
			"setMaxCooldown", &Cooldown::setMaxCooldown
		);
	}
};
