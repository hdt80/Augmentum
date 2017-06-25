#pragma once

#include <sol/sol.hpp>

namespace LuaDefines {

	// Define all the classes for a sol::state by calling the individual class
	//		defines for all types
	//
	// lua - sol::state to define the classes for
	//
	void defineClasses(sol::state& lua);

	// Class definitions ///////////////////////////////////////////////////////

	// Each of these will define the single class for the sol::state
	//
	// lua - sol::state to define the single class for
	//

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
	void defineVector2(sol::state& lua);
};
