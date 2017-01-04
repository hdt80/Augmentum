#include "lua/LuaDefines.h"

#include "Unit.h"
#include "Map.h"
#include <SFML/Graphics.hpp>

namespace LuaDefines {

	void defineUnit(sol::state& lua) {
		lua.new_usertype<Unit> (
			"Unit", sol::constructors<
				sol::types<
					Map*, float, float, Stats, Stats, int, int, sf::Color>>(),
			"collidesWith", &Unit::collidesWith,
			"isSimpleTarget", &Unit::isSimpleTarget,
			"applyStat", &Unit::applyStat,
			"setStats", &Unit::setStats,
			"getStatMod", &Unit::getStatMod,
			"getStats", &Unit::getStats,
			"getBaseStats", &Unit::getBaseStats,
			"getStat", &Unit::getStat,
			"setStat", &Unit::setStat,
			"addPerk", &Unit::addPerk,
			"removePerk", &Unit::removePerk,
			"getMap", &Unit::getMap,
			"getSize", &Unit::getSize,
			"getPerks", &Unit::getPerks,
			"getTarget", &Unit::getTarget,
			"getDirection", &Unit::getDirection,
			"getAttackerCount", &Unit::getAttackerCount,
			"setVelocity", &Unit::setVelocity,
			"getVelocity", &Unit::getVelocity,
			"getX", &Unit::getX,
			"getY", &Unit::getY,
			"contains", &Unit::contains,
			"canShoot", &Unit::canShoot,
			"applyDamage", &Unit::applyDamage,
			"getHealth", &Unit::getHealth,
			"getMaxHealth", &Unit::getMaxHealth,
			"getHealthGone", &Unit::getHealthGone,
			"setHealth", &Unit::setHealth,
			"setMaxHealth", &Unit::setMaxHealth,
			"getExpToNextLevel", &Unit::getExpToNextLevel,
			"getExpForCurrentLevel", &Unit::getExpForCurrentLevel,
			"getLevel", &Unit::getLevel,
			"addExp", &Unit::addExp,
			"setExp", &Unit::setExp,
			"setLevel", &Unit::setLevel
		);
	}
};
