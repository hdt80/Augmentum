#include "lua/LuaDefines.h"

#include "Unit.h"
#include "Map.h"
#include <SFML/Graphics.hpp>

namespace LuaDefines {
	void defineUnit(sol::state& lua) {
		lua.new_usertype<Unit> (
			"Unit", sol::constructors<
				sol::types<Map*, float, float, Stats, Stats, int, int,
					sf::Color>>(),
			"distanceWith", sol::overload(sol::resolve
				<float(float, float)>(&Unit::distanceWith)),
			"distanceWithSqr", sol::overload(sol::resolve
				<float(float, float)>(&Unit::distanceWithSqr)),
			"getX", &Unit::getX,
			"getY", &Unit::getY,
			"isSimpleTarget", &Unit::isSimpleTarget,
			"getObjectType", &Unit::getObjectType,
			"isObjectTypeOptionSet", &Unit::isObjectTypeOptionSet,
			"setVelocity", &Unit::setVelocity,
			"updatePosition", &Unit::updatePosition,
			"setPosition", sol::overload(
				sol::resolve<void(float, float)>(&Unit::setPosition)),
			"getSize", &Unit::getSize,
			"hasCollision", &Unit::hasCollision,
			"contains", &Unit::contains,
			"collidesWith", &Unit::collidesWith,
			"getMap", &Unit::getMap,
			"isToRemove", &Unit::isToRemove,
			"getVelocity", &Unit::getVelocity,
			"getX", &Unit::getX,
			"getY", &Unit::getY,
			"dealDamage", &Unit::dealDamage,
			"setHealth", &Unit::setHealth,
			"getHealth", sol::overload(
				sol::resolve<float(void) const>(&Unit::getHealth)),
			"setHealth", &Unit::setHealth,
			"getMaxHealth", sol::overload(
				sol::resolve<float(void) const>(&Unit::getMaxHealth)),
			"setMaxHealth", &Unit::setMaxHealth,
			"isInvulerable", &Unit::isInvulerable,
			"setInvulerable", &Unit::setInvulerable,
			"canShoot", &Unit::canShoot,
			"shoot", sol::overload(
				sol::resolve<void(float, float)>(&Unit::shoot)),
			"getExpToNextLevel", &Unit::getExpToNextLevel,
			"getExpForCurrentLevel", &Unit::getExpForCurrentLevel,
			"getLevel", &Unit::getLevel,
			"getExp", sol::overload(
				sol::resolve<float(void) const>(&Unit::getExp)),
			"addExp", &Unit::addExp,
			"setExp", &Unit::setExp,
			"setLevel", &Unit::setLevel,
			"applyStat", &Unit::applyStat,
			"setStats", &Unit::setStats,
			"getStatMod", &Unit::getStatMod,
			"getStats", &Unit::getStats,
			"getBaseStats", &Unit::getBaseStats,
			"getStat", &Unit::getStat,
			"setStat", &Unit::setStat,
			"getPerks", &Unit::getPerks,
			"addPerk", &Unit::addPerk,
			"removePerk", &Unit::removePerk,
			"hasPerk", &Unit::hasPerk,
			"getPerk", &Unit::getPerk
		);
	}
};
