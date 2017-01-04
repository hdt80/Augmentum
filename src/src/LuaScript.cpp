#include "LuaScript.h"
#include "Logger.h"
#include "Object.h"
#include "Map.h"
#include "Target.h"
#include "Enemy.h"
#include "Perk.h"
#include "Stats.h"
#include "lua/LuaDefines.h"

LuaScript::LuaScript(bool defineClasses) {
	_loaded = false;
	lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table,
		sol::lib::package, sol::lib::math, sol::lib::debug);

	if (defineClasses) {
		LuaDefines::defineClasses(lua);
	}
}

void LuaScript::loadScript(const std::string& path) {
	try {
		_name = path;
		lua.script_file(path);
		_loaded = true;
	} catch (sol::error e) {
		setLoaded(false);
		CORE_ERROR("[Lua Script %x] Error when loading from \"%s\": %s",
			this, path.c_str(), e.what());
	}
}

void LuaScript::printTable() {
	auto iter = lua.begin();
	CORE_INFO("[LuaScript %x] Print %s", this, _name.c_str());
	while (iter != lua.end()) {
		CORE_INFO("%s", (*iter).first.as<std::string>().c_str());
		++iter;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Static methods
////////////////////////////////////////////////////////////////////////////////

//void LuaScript::defineClasses(sol::state& lua) {
//	defineObject(lua);
//	defineEnemy(lua);
//	defineTarget(lua);
//	defineMap(lua);
//	defineStats(lua);
//	definePerk(lua);
//}

////////////////////////////////////////////////////////////////////////////////
// Object defenitions for Lua scripts
////////////////////////////////////////////////////////////////////////////////

//void LuaScript::defineObject(sol::state& lua) {
//	lua.new_simple_usertype<Object> (
//		"Object", sol::constructors<
//			sol::types<Map*, float, float, Stats, int>>(),
//		"getX", &Object::getX,
//		"getY", &Object::getY,
//		// Object methods
//		"contains", &Object::contains,
//		"applyStat", &Object::applyStat,
//		"setStats", &Object::setStats,
//		"getSpeed", &Object::getSpeed,
//		"getRange", &Object::getRange,
//		"setRange", &Object::setRange
//	);
//}
//
//void LuaScript::defineTarget(sol::state& lua) {
//	lua.new_simple_usertype<Target> (
//		"Target", sol::constructors<sol::types<float, float>>(),
//		"getX", &Target::getX,
//		"getY", &Target::getY,
//		"setPosition", &Target::setPosition,
//		"isSimpleTarget", &Target::isSimpleTarget
//	);
//}
//
//void LuaScript::defineMap(sol::state& lua) {
//
//}
//
//void LuaScript::defineStats(sol::state& lua) {
//	lua.new_simple_usertype<Stats> (
//		"Stats", sol::constructors<sol::types<bool>>(),		
//		"print", &Stats::print,
//		"addStat", &Stats::addStat,
//		"setStat", &Stats::setStat,
//		"hasStat", &Stats::hasStat,
//		"getStat", &Stats::getStat
//	);
//}
//
//void LuaScript::definePerk(sol::state& lua) {
//	lua.new_simple_usertype<Perk> (
//		"Perk", sol::constructors<
//				sol::types<std::string, Stats, float, bool, int>>(),
//		"getName", &Perk::getName,
//		"getTitle", &Perk::getTitle
//	//	"getStats", &Perk::getStats // TODO: Ambigious call?
//	);
//}
//
//void LuaScript::defineEnemy(sol::state& lua) {
//	lua.new_simple_usertype<Enemy> (
//		"Enemy", sol::constructors<
//				sol::types<Map*, float, float, int, EnemyType>>(),
//		// Target methods
//		"getX", &Enemy::getX,
//		"getY", &Enemy::getY,
//		//"distanceWith", &Enemy::distanceWith,
//		//"distanceWithSqr", &Enemy::distanceWithSqr,
//		"isSimpleTarget", &Enemy::isSimpleTarget,
//		// Object methods
//		"contains", &Enemy::contains,
//		"applyStat", &Enemy::applyStat,
//		"setStats", &Enemy::setStats,
//		"getSpeed", &Enemy::getSpeed,
//		"getRange", &Enemy::getRange,
//		"getFireRate", &Enemy::getFireRate,
//		"getDamage", &Enemy::getDamage,
//		"getAccel", &Enemy::getAccel,
//		// Enemy methods
//		"applyDamage", &Enemy::applyDamage,
//		"getHealth", &Enemy::getHealth,
//		"getMaxHealth", &Enemy::getMaxHealth,
//		"setHealth", &Enemy::setHealth,
//		"setMaxHealth", &Enemy::setMaxHealth,
//		"setTarget", &Enemy::setTarget
//	);
//}
