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
			"getX", &Asteroid::getX,
			"getY", &Asteroid::getY,
			"isSimpleTarget", &Asteroid::isSimpleTarget,
			"getObjectType", &Asteroid::getObjectType,
			"isObjectTypeOptionSet", &Asteroid::isObjectTypeOptionSet,
			"setVelocity", &Asteroid::setVelocity,
			"updatePosition", &Asteroid::updatePosition,
			"setPosition", sol::overload(
				sol::resolve<void(float, float)>(&Asteroid::setPosition)),
			"getSize", &Asteroid::getSize,
			"hasCollision", &Asteroid::hasCollision,
			"contains", &Asteroid::contains,
			"collidesWith", &Asteroid::collidesWith,
			"getMap", &Asteroid::getMap,
			"isToRemove", &Asteroid::isToRemove,
			"getVelocity", &Asteroid::getVelocity,
			"getX", &Asteroid::getX,
			"getY", &Asteroid::getY,
			"dealDamage", &Asteroid::dealDamage,
			"setHealth", &Asteroid::setHealth,
			"getHealth", sol::overload(
				sol::resolve<float(void) const>(&Asteroid::getHealth)),
			"setHealth", &Asteroid::setHealth,
			"getMaxHealth", sol::overload(
				sol::resolve<float(void) const>(&Asteroid::getMaxHealth)),
			"setMaxHealth", &Asteroid::setMaxHealth,
			"isInvulerable", &Asteroid::isInvulerable,
			"setInvulerable", &Asteroid::setInvulerable,
			"getMaxRadius", &Asteroid::getMaxRadius,
			"getDrift", &Asteroid::getDrift,
			"setDrift", sol::overload(
				sol::resolve<void(float, float)>(&Asteroid::setDrift))
		);
	}
};
