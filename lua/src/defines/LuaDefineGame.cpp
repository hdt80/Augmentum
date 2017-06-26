#include "lua/LuaDefines.h"

#include "game/Game.h"

namespace LuaDefines {
	void defineGame(sol::state& lua) {
		lua.set_function("game_step", [](int diff) {
			Game::step(diff);
		});
	}
};
