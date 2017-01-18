#include "lua/LuaDefines.h"

#include "environment/Asteroid.h"
#include "Map.h"

namespace LuaDefines {

	void defineAsteroid(sol::state& lua) {
		lua.new_usertype<Asteroid> (
			"Asteroid", sol::constructors<
				sol::types<Map*, float, float, float>>(),
			"distanceWith", sol::overload(sol::resolve
				<float(float, float)>(&Asteroid::distanceWith)),
			"distanceWithSqr", sol::overload(sol::resolve
				<float(float, float)>(&Asteroid::distanceWithSqr)),
			"collidesWith", &Asteroid::collidesWith,
			"isSimpleTarget", &Asteroid::isSimpleTarget,
			"applyStat", &Asteroid::applyStat,
			"setStats", &Asteroid::setStats,
			"getStatMod", &Asteroid::getStatMod,
			"getStats", &Asteroid::getStats,
			"getBaseStats", &Asteroid::getBaseStats,
			"getStat", &Asteroid::getStat,
			"setStat", &Asteroid::setStat,
			"addPerk", &Asteroid::addPerk,
			"removePerk", &Asteroid::removePerk,
			"hasPerk", &Asteroid::hasPerk,
			"getPerk", sol::overload(sol::resolve
				<Perk*(const std::string& name) const>(&Asteroid::getPerk)),
			"getMap", &Asteroid::getMap,
			"getSize", &Asteroid::getSize,
			"getPerks", &Asteroid::getPerks,
			"getTarget", &Asteroid::getTarget,
			"getDirection", &Asteroid::getDirection,
			"getAttackerCount", &Asteroid::getAttackerCount,
			"setVelocity", &Asteroid::setVelocity,
			"getVelocity", &Asteroid::getVelocity,
			"setPosition", sol::overload(
				sol::resolve<void(float, float)>(&Asteroid::setPosition)),
			"getX", &Asteroid::getX,
			"getY", &Asteroid::getY,
			"contains", &Asteroid::contains,
			"getMaxRadius", &Asteroid::getMaxRadius,
			"getDrift", &Asteroid::getDrift,
			"setDrift", sol::overload(
				sol::resolve<void(float, float)>(&Asteroid::setDrift))
		);
	}
};
