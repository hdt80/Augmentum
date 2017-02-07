#include "lua/LuaDefines.h"

#include "Perk.h"
#include "Unit.h"

namespace LuaDefines {
	void definePerk(sol::state& lua) {
		lua.new_usertype<Perk> (
			"Perk", sol::constructors<sol::types<
				const std::string&, Stats, float, bool, int>>(),
			"update", &Perk::update,
			"setAttached", &Perk::setAttached,
			"getAttached", &Perk::getAttached,
			"getDuration", &Perk::getDuration,
			"setDuration", &Perk::setDuration,
			"getShortDuration", &Perk::getShortDuration,
			"getMaxDuration", &Perk::getMaxDuration,
			"getShortMaxDuration", &Perk::getShortMaxDuration,
			"getStacks", &Perk::getStacks,
			"getMaxStacks", &Perk::getMaxStacks,
			"isStackable", &Perk::isStackable,
			"setStackable", &Perk::setStackable,
			"setStacks", &Perk::setStacks,
			"addStack", &Perk::addStack,
			"removeStack", &Perk::removeStack,
			"isToRemove", &Perk::isToRemove,
			"getName", &Perk::getName,
			"getTitle", &Perk::getTitle,
			"getStats", sol::overload(
				sol::resolve<const Stats&() const>(&Perk::getStats))
		);
	}
};
