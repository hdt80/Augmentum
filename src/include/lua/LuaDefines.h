#ifndef _LUA_DEFINES_H
#define _LUA_DEFINES_H

#include "sol/sol.hpp"
#include "Logger.h"

namespace LuaDefines {

	// Define all the classes for a sol::state
	// lua - sol::state to define the classes for
	void defineClasses(sol::state& lua);

	// Class definitions ///////////////////////////////////////////////////////

	void defineTarget(sol::state& lua);
	void defineObject(sol::state& lua);
	void defineCooldown(sol::state& lua);
	void defineEnemy(sol::state& lua);
	void defineGame(sol::state& lua);
	void defineAsteroid(sol::state& lua);
	void defineEntity(sol::state& lua);
	void defineMap(sol::state& lua);
	void defineParticleEmitter(sol::state& lua);
	void definePerk(sol::state& lua);
	void defineProjectile(sol::state& lua);
	void defineShip(sol::state& lua);
	void defineStats(sol::state& lua);
	void defineUnit(sol::state& lua);
	void defineVector2(sol::state& lua); // TODO
};

#endif
