#include "Enemy.h"
#include "Map.h"
#include "ParticleEmitter.h"
#include "Ship.h"

#include "Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Enemy ctor and dtor
////////////////////////////////////////////////////////////////////////////////

Enemy::Enemy(Map* map, float x, float y, int size, const EnemyType& type)
	: Unit(map, x, y, type.getDefaultStats(), type.getLevelDiffStats(), size,
			type.getSides(), sf::Color::Red),
		_enemyType(type) {

	_shape.setRadius(size);
	_shape.setFillColor(sf::Color::Red);

	setObjectType(ObjectType::ENEMY);

	loadLua();
	_lua.loadScript("./lua/enemy.lua");
}

Enemy::~Enemy() {}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////

void Enemy::update(int diff) {
	Unit::update(diff);

	if (_reload.done()) {
		// Make sure we have a Target to shoot at
		if (distanceWith(_map->getSelected()) <= getRange()) {
			shoot(_map->getSelected()->getX(), _map->getSelected()->getY());
		} else {
			// Start the shooting regardless if there was a shot or not
			_reload.start();
		}
	}
}

void Enemy::loadLua() {
	if (_lua.isLoaded()) {
		CORE_ERROR("[Enemy: %x] Setting up a loaded Lua at %x", this, &_lua);
	}
	Object::loadLua();

	_lua.lua.set("me", this); // Set a reference to this in the lua script
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	Unit::draw(target, states);

	// Draw the range of the Enemy
	sf::CircleShape rng;
	rng.setRadius(getRange());
	rng.setPosition(getX() - (getRange()), getY() - (getRange()));
	rng.setFillColor(sf::Color::Transparent);
	rng.setOutlineColor(sf::Color::Red);
	rng.setOutlineThickness(3.0f);

	target.draw(rng);
}
