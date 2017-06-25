#include "LuaDefines.h"

#include "game/ParticleEmitter.h"

namespace LuaDefines {
	void defineParticleEmitter(sol::state& lua) {
		lua.new_usertype<ParticleEmitter> (
			"ParticleEmitter", sol::constructors<>(),
			"emit", sol::overload(sol::resolve<void(const std::string&,
				float, float, int, float)>(&ParticleEmitter::emit)),
			"update", &ParticleEmitter::update,
			"getParticleCount", &ParticleEmitter::getParticleCount
		);
	}
};
