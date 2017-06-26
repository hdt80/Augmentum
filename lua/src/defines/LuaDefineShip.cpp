#include "lua/LuaDefines.h"

#include "game/Map.h"
#include "game/Ship.h"

//#include <SFML/Graphics.hpp>

namespace LuaDefines {
	void defineShip(sol::state& lua) {
		lua.new_usertype<Ship> (
			"Ship", sol::constructors<
				sol::types<
					Map*, float, float, Stats, Stats, int, int, sf::Color>>(),
			"distanceWith", sol::overload(sol::resolve
				<float(float, float)>(&Ship::distanceWith)),
			"distanceWithSqr", sol::overload(sol::resolve
				<float(float, float)>(&Ship::distanceWithSqr)),
			"getX", &Ship::getX,
			"getY", &Ship::getY,
			"isSimpleTarget", &Ship::isSimpleTarget,
			"getObjectType", &Ship::getObjectType,
			"isObjectTypeOptionSet", &Ship::isObjectTypeOptionSet,
			"setVelocity", &Ship::setVelocity,
			"updatePosition", &Ship::updatePosition,
			"setPosition", sol::overload(
				sol::resolve<void(float, float)>(&Ship::setPosition)),
			"getSize", &Ship::getSize,
			"hasCollision", &Ship::hasCollision,
			"contains", &Ship::contains,
			"collidesWith", &Ship::collidesWith,
			"getMap", &Ship::getMap,
			"isToRemove", &Ship::isToRemove,
			"getVelocity", &Ship::getVelocity,
			"getX", &Ship::getX,
			"getY", &Ship::getY,
			"dealDamage", &Ship::dealDamage,
			"setHealth", &Ship::setHealth,
			"getHealth", sol::overload(
				sol::resolve<float(void) const>(&Ship::getHealth)),
			"setHealth", &Ship::setHealth,
			"getMaxHealth", sol::overload(
				sol::resolve<float(void) const>(&Ship::getMaxHealth)),
			"setMaxHealth", &Ship::setMaxHealth,
			"isInvulerable", &Ship::isInvulerable,
			"setInvulerable", &Ship::setInvulerable,
			"canShoot", &Ship::canShoot,
			"shoot", sol::overload(
				sol::resolve<void(float, float)>(&Ship::shoot)),
			"getExpToNextLevel", &Ship::getExpToNextLevel,
			"getExpForCurrentLevel", &Ship::getExpForCurrentLevel,
			"getLevel", &Ship::getLevel,
			"getExp", sol::overload(
				sol::resolve<float(void) const>(&Ship::getExp)),
			"addExp", &Ship::addExp,
			"setExp", &Ship::setExp,
			"setLevel", &Ship::setLevel,
			"applyStat", &Ship::applyStat,
			"setStats", &Ship::setStats,
			"getStatMod", &Ship::getStatMod,
			"getStats", &Ship::getStats,
			"getBaseStats", &Ship::getBaseStats,
			"getStat", &Ship::getStat,
			"setStat", &Ship::setStat,
			"getPerks", &Ship::getPerks,
			"addPerk", &Ship::addPerk,
			"removePerk", &Ship::removePerk,
			"hasPerk", &Ship::hasPerk,
			"getPerk", &Ship::getPerk,
			"getSideCount", &Ship::getSideCount,
			"setToRemove", &Ship::setToRemove
		);
	}
};
