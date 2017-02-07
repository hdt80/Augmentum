#include "lua/LuaDefines.h"

#include "Vector2.h"

namespace LuaDefines {
	void defineVector2(sol::state& lua) {
		lua.new_usertype<Vector2>(
			"Vector2", sol::constructors<sol::types<float, float>>(),
			"length", &Vector2::length,
			"sqrtLength", &Vector2::sqrtLength,
			"angle", &Vector2::angle,
			"normalize", &Vector2::normalize
		);
	}
};
