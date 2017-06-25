#include "LuaDefines.h"

namespace LuaDefines {
	void defineClasses(sol::state& lua) {
		defineTarget(lua);
		defineObject(lua);
		defineCooldown(lua);
		defineEnemy(lua);
		defineEntity(lua);
		defineGame(lua);
		defineAsteroid(lua);
		defineMap(lua);
		defineParticleEmitter(lua);
		definePerk(lua);
		defineProjectile(lua);
		defineShip(lua);
		defineStats(lua);
		defineUnit(lua);
		defineVector2(lua);
	}
};
