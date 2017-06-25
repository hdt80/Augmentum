#include "LuaDefines.h"

#include "game/Map.h"
#include "game/Ship.h"

namespace LuaDefines {
	void defineMap(sol::state& lua) {
		lua.new_usertype<Map> (
			"Map", sol::constructors<>(),
			"update", &Map::update,
			"updateBox2D", &Map::updateBox2D,
			"reset", &Map::reset,
			"getSelected", &Map::getSelected,
			"getWorld", &Map::getWorld,
			"getObjectsInRange", sol::overload(sol::resolve
				<std::vector<Object*>(float, float, float)>
					(&Map::getObjectsInRange)),
			"collisionAtPlace", &Map::collisionAtPlace,
			"objectAt", &Map::objectAt,
			"spawnEnemy", &Map::spawnEnemy,
			"spawnAsteroid", &Map::spawnAsteroid,
			"dumpObjects", &Map::dumpObjects
		);
	}
};
