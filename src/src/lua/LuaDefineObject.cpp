
#include "lua/LuaDefines.h"

#include "Object.h"
#include "Map.h" // Required for the sol::constructors

namespace LuaDefines {

	void defineObject(sol::state& lua) {
		lua.new_usertype<Object> (
			"Object", sol::constructors<
				sol::types<Map*, float, float, Stats, int>>(),
			"distanceWith", sol::overload(sol::resolve
				<float(float, float)>(&Object::distanceWith)),
			"distanceWithSqr", sol::overload(sol::resolve
				<float(float, float)>(&Object::distanceWithSqr)),
			"collidesWith", &Object::collidesWith,
			"isSimpleTarget", &Object::isSimpleTarget,
			"applyStat", &Object::applyStat,
			"setStats", &Object::setStats,
			"getStatMod", &Object::getStatMod,
			"getStats", &Object::getStats,
			"getBaseStats", &Object::getBaseStats,
			"getStat", &Object::getStat,
			"setStat", &Object::setStat,
			"addPerk", &Object::addPerk,
			"removePerk", &Object::removePerk,
			"hasPerk", &Object::hasPerk,
			"getPerk", sol::overload(sol::resolve
				<Perk*(const std::string& name) const>(&Object::getPerk)),
			"getMap", &Object::getMap,
			"getSize", &Object::getSize,
			"getPerks", &Object::getPerks,
			"getTarget", &Object::getTarget,
			"getDirection", &Object::getDirection,
			"getAttackerCount", &Object::getAttackerCount,
			"setVelocity", &Object::setVelocity,
			"getVelocity", &Object::getVelocity,
			"setPosition", sol::overload(
				sol::resolve<void(float, float)>(&Object::setPosition)),
			"getX", &Object::getX,
			"getY", &Object::getY,
			"contains", &Object::contains
		);
	}
};
