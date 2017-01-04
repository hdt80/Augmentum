#include "lua/LuaDefines.h"

#include "Target.h"

namespace LuaDefines {

	void defineTarget(sol::state& lua) {
		lua.new_usertype<Target> (
			"Target", sol::constructors<sol::types<float, float>>(),
			"getX", &Target::getX,
			"getY", &Target::getY,
			"setPosition", &Target::setPosition,
			"isSimpleTarget", &Target::isSimpleTarget
		);
	}
};
