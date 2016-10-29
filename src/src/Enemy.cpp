#include "Enemy.h"
#include "Map.h"
#include "ParticleEmitter.h"
#include "Common.h"

#include "Logger.h"

////////////////////////////////////////////////////////////////////////////////
// EnemyType static methods
////////////////////////////////////////////////////////////////////////////////

EnemyType* EnemyType::getById(int id) {
	if (!idInUse(id)) {
		CORE_WARN("getById: id not in use! (%d)", id);
		return getDefaultType();
	}
	return &_types[id];
}

bool EnemyType::idInUse(unsigned int id) {
	return id < _types.size();
}

int EnemyType::createEnemyType(int id, const std::string& name, int sides,
	Stats defStats, Stats levelDiff) {

	// If the id is already in use try to use the next one
	if (idInUse(id)) {
		CORE_WARN("CreateEnemyType: id %d is already in use!", id);
		CORE_WARN("Trying to use %d to create", id + 1);
		return createEnemyType(++id, name, sides, defStats, levelDiff);
	}

	_types.push_back(EnemyType(id, name, sides, defStats, levelDiff));

	return id;
}

EnemyType* EnemyType::getDefaultType() {
	return &_defaultType;
}

////////////////////////////////////////////////////////////////////////////////
// EnemyType static vars
////////////////////////////////////////////////////////////////////////////////

std::vector<EnemyType> EnemyType::_types;
EnemyType EnemyType::_defaultType(0, "DEFAULT", 4, Stats(), Stats());

///////////////////////////////////////////////////////////////////////////////
// Constuctor and deconstrctor
///////////////////////////////////////////////////////////////////////////////

EnemyType::EnemyType(int id, const std::string& name, int sides,
		Stats defStats, Stats levelDiff)
	: _id(id), _name(name), _sides(sides), _defaultStats(defStats),
		_levelDiff(levelDiff) {

}

///////////////////////////////////////////////////////////////////////////////
// Constuctor and deconstrctor
///////////////////////////////////////////////////////////////////////////////

Enemy::Enemy(Map* map, float x, float y, EnemyType type)
	: Unit(map, x, y, type.getDefaultStats(), type.getSides(), sf::Color::Red),
		_enemyType(type) {

	_shape.setRadius(20);
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

//void Enemy::update(int diff) {
//	Object::update(diff);
//}
