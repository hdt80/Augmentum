#include "LuaDefines.h"

#include "game/Object.h"
#include "game/Map.h" // Required for the sol::constructors

namespace LuaDefines {
	void defineObject(sol::state& lua) {
		lua.new_usertype<Object> (
			"Object", sol::constructors<
				sol::types<Map*, float, float, int>>(),
			"distanceWith", sol::overload(sol::resolve
				<float(float, float)>(&Object::distanceWith)),
			"distanceWithSqr", sol::overload(sol::resolve
				<float(float, float)>(&Object::distanceWithSqr)),
			"getX", &Object::getX,
			"getY", &Object::getY,
			"isSimpleTarget", &Object::isSimpleTarget,
			"getObjectType", &Object::getObjectType,
			"isObjectTypeOptionSet", &Object::isObjectTypeOptionSet,
			"setVelocity", &Object::setVelocity,
			"updatePosition", &Object::updatePosition,
			"setPosition", sol::overload(
				sol::resolve<void(float, float)>(&Object::setPosition)),
			"getSize", &Object::getSize,
			"hasCollision", &Object::hasCollision,
			"contains", &Object::contains,
			"collidesWith", &Object::collidesWith,
			"getMap", &Object::getMap,
			"isToRemove", &Object::isToRemove,
			"getVelocity", &Object::getVelocity,
			"getX", &Object::getX,
			"getY", &Object::getY,
			"setToRemove", &Object::setToRemove
		);
	}
};
