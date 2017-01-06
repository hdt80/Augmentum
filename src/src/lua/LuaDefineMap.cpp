#include "lua/LuaDefines.h"

#include "Map.h"
#include "Ship.h"

namespace LuaDefines {

	void defineMap(sol::state& lua) {
		lua.new_usertype<Map> (
			"Map", sol::constructors<>(),
			"update", &Map::update,
			"getSelected", &Map::getSelected,
			"getWorld", &Map::getWorld,
			"getObjectsInRange", sol::overload(sol::resolve
				<std::vector<Object*>(float, float, float)>
				(&Map::getObjectsInRange)),
			"collisionAtPlace", &Map::collisionAtPlace,
			"objectAt", &Map::objectAt,
			"spawnEnemy", &Map::spawnEnemy,
			"spawnAsteroid", &Map::spawnAsteroid
		);
	}
};
