#include "lua/LuaDefines.h"

#include "Map.h"
#include "Ship.h"
#include <SFML/Graphics.hpp>

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
			"collidesWith", &Ship::collidesWith,
			"isSimpleTarget", &Ship::isSimpleTarget,
			"applyStat", &Ship::applyStat,
			"setStats", &Ship::setStats,
			"getStatMod", &Ship::getStatMod,
			"getStats", &Ship::getStats,
			"getBaseStats", &Ship::getBaseStats,
			"getStat", &Ship::getStat,
			"setStat", &Ship::setStat,
			"addPerk", &Ship::addPerk,
			"removePerk", &Ship::removePerk,
			"hasPerk", &Ship::hasPerk,
			"getPerk", sol::overload(sol::resolve
				<Perk*(const std::string& name) const>(&Ship::getPerk)),
			"getMap", &Ship::getMap,
			"getSize", &Ship::getSize,
			"getPerks", &Ship::getPerks,
			"getTarget", &Ship::getTarget,
			"getDirection", &Ship::getDirection,
			"getAttackerCount", &Ship::getAttackerCount,
			"setVelocity", &Ship::setVelocity,
			"getVelocity", &Ship::getVelocity,
			"setPosition", sol::overload(
				sol::resolve<void(float, float)>(&Ship::setPosition)),
			"getX", &Ship::getX,
			"getY", &Ship::getY,
			"contains", &Ship::contains,
			"canShoot", &Ship::canShoot,
			"shoot", sol::overload(
				sol::resolve<void(float, float)>(&Ship::shoot),
				sol::resolve<void(Target*)>(&Ship::shoot)),
			"applyDamage", &Ship::applyDamage,
			"getHealth", &Ship::getHealth,
			"getMaxHealth", &Ship::getMaxHealth,
			"getHealthGone", &Ship::getHealthGone,
			"setHealth", &Ship::setHealth,
			"setMaxHealth", &Ship::setMaxHealth,
			"getExpToNextLevel", &Ship::getExpToNextLevel,
			"getExpForCurrentLevel", &Ship::getExpForCurrentLevel,
			"getLevel", &Ship::getLevel,
			"addExp", &Ship::addExp,
			"setExp", &Ship::setExp,
			"setLevel", &Ship::setLevel,
			"getSideCount", &Ship::getSideCount,
			"getColor", &Ship::getColor
		);
	}
};
