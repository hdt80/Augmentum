#include "game/ParticleDef.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

ParticleDef::ParticleDef(const sol::table& table)
	: LuaConfigEntry("ParticleDef") {

	readFromTable(table);
}

ParticleDef::ParticleDef()
	: LuaConfigEntry("ParticleDef"),
		_lifetime(0.0f), _coneOfDispersion(0.0f), _speedVariation(0.0f),
		_initColor(sf::Color::Transparent), _endColor(_initColor), _fade(false),
		_speed(0.0f), _slowDown(false) {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void ParticleDef::readFromTable(const sol::table& table) {
	_lifetime = table.get<float>("lifeTime");
	
	_coneOfDispersion = table.get<float>("coneOfDispersion");
	_speedVariation = table.get<float>("speedVariation");

	_initColor = getSfColor(table["initColor"]);
	_endColor = getSfColor(table["endColor"]);
	_fade = table.get<bool>("fade");

	_speed = table.get<float>("speed");
	_slowDown = table.get<bool>("slowDown");
}
