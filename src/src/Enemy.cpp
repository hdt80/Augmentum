#include "Enemy.h"
#include "Map.h"
#include "ParticleEmitter.h"
#include "Common.h"

#include "Logger.h"

////////////////////////////////////////////////////////////////////////////////
// EnemyType
////////////////////////////////////////////////////////////////////////////////

EnemyType EnemyType::getById(int id) {

}

void EnemyType::createEnemyType(int id, const std::string& name, int sides,
	Stats defStats, Stats levelDiff) {

}

///////////////////////////////////////////////////////////////////////////////
// Constuctor and deconstrctor
///////////////////////////////////////////////////////////////////////////////

Enemy::Enemy(Map* map, float x, float y, EnemyType type)
	: Unit(map, x, y, type.getDefaultStats(), type.getSides(), sf::Color::Red) {

	_shape.setRadius(ENEMY_WIDTH);
	_shape.setFillColor(sf::Color::Red);

	_hpBar.setFillColor(sf::Color::Green);

	loadLua();
	_lua.loadScript("./lua/enemy.lua");
}

Enemy::~Enemy() {}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////

void Enemy::loadLua() {
	if (_lua.isLoaded()) {
		CORE_ERROR("[Enemy: %x] Setting up a loaded Lua at %x", this, &_lua);
	}
	Object::loadLua();

	_lua.lua.set("me", this);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_shape);
	target.draw(_hpBar);
}

void Enemy::update(int diff) {
	Object::update(diff);
}
