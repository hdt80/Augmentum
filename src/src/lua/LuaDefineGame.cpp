#include "lua/LuaDefines.h"

#include "Game.h"

namespace LuaDefines {

	void defineGame(sol::state& lua) {
		lua.set_function("game_step", [](int diff) {
			Game::step(diff);
		});
	}
};
