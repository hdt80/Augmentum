#include "lua/LuaDefines.h"

#include "Object.h"
#include "Map.h" // Required for the sol::constructors

namespace LuaDefines {
	void defineEntity(sol::state& lua) {
		lua.new_usertype<Entity> (
			"Entity", sol::constructors<
				sol::types<Map*, float, float, int, int>>(),
			"distanceWith", sol::overload(sol::resolve
				<float(float, float)>(&Entity::distanceWith)),
			"distanceWithSqr", sol::overload(sol::resolve
				<float(float, float)>(&Entity::distanceWithSqr)),
			"getX", &Entity::getX,
			"getY", &Entity::getY,
			"isSimpleTarget", &Entity::isSimpleTarget,
			"getObjectType", &Entity::getObjectType,
			"isObjectTypeOptionSet", &Entity::isObjectTypeOptionSet,
			"setVelocity", &Entity::setVelocity,
			"updatePosition", &Entity::updatePosition,
			"setPosition", sol::overload(
				sol::resolve<void(float, float)>(&Entity::setPosition)),
			"getSize", &Entity::getSize,
			"hasCollision", &Entity::hasCollision,
			"contains", &Entity::contains,
			"collidesWith", &Entity::collidesWith,
			"getMap", &Entity::getMap,
			"isToRemove", &Entity::isToRemove,
			"getVelocity", &Entity::getVelocity,
			"getX", &Entity::getX,
			"getY", &Entity::getY,
			"dealDamage", &Entity::dealDamage,
			"setHealth", &Entity::setHealth,
			"getHealth", sol::overload(
				sol::resolve<float(void) const>(&Entity::getHealth)),
			"setHealth", &Entity::setHealth,
			"getMaxHealth", sol::overload(
				sol::resolve<float(void) const>(&Entity::getMaxHealth)),
			"setMaxHealth", &Entity::setMaxHealth,
			"isInvulerable", &Entity::isInvulerable,
			"setInvulerable", &Entity::setInvulerable,
			"setToRemove", &Entity::setToRemove
		);
	}
};
