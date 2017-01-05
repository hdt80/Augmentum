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
	void defineCooldown(sol::state& lua); // TODO
	void defineEnemy(sol::state& lua); // TODO
	void defineGame(sol::state& lua); // TODO
	void defineAsteroid(sol::state& lua); // TODO
	void defineMap(sol::state& lua); // TODO
	void defineParticleEmitter(sol::state& lua); // TODO
	void definePerk(sol::state& lua); // TODO
	void defineProjectile(sol::state& lua); // TODO
	void defineShip(sol::state& lua);
	void defineStats(sol::state& lua); // TODO
	void defineUnit(sol::state& lua);
	void defineVector2(sol::state& lua); // TODO
};

#endif