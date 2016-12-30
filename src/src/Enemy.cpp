#include "Enemy.h"
#include "Map.h"
#include "ParticleEmitter.h"
#include "Common.h"

#include "Logger.h"
#include "Ship.h"

////////////////////////////////////////////////////////////////////////////////
// EnemyType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// EnemyType static methods
////////////////////////////////////////////////////////////////////////////////

EnemyType* EnemyType::getById(int id) {
	if (!idInUse(id)) {
		CORE_WARN("getById: id not in use! (%d)", id);
		return getDefaultType();
	}
	return &_types.at(id);
}

bool EnemyType::idInUse(unsigned int id) {
	std::map<int, EnemyType>::iterator it = _types.find(id);
	return (it != _types.end());
}

int EnemyType::createEnemyType(int id, const std::string& name, int sides,
	Stats defStats, Stats levelDiff) {

	// If the id is already in use try to use the next one
	if (idInUse(id)) {
		CORE_WARN("CreateEnemyType: id %d is already in use!", id);
		CORE_WARN("Trying to use %d to create", id + 1);
		return createEnemyType(++id, name, sides, defStats, levelDiff);
	}

	_types.insert(std::map<int, EnemyType>
		::value_type(id, EnemyType(id, name, sides, defStats, levelDiff)));

	CORE_DEBUG("Created enemy type");
	CORE_DEBUG("\tid: %d", id);
	CORE_DEBUG("\tname: %s", name.c_str());

	return id;
}

EnemyType* EnemyType::getDefaultType() {
	return &_defaultType;
}

int EnemyType::loadEnemyType(const std::string& path) {
	// Create a temp EnemyType to load the values into
	EnemyType type(0, "", 0, Stats(), Stats());

	type.readFromFile(path);

	addEnemyType(type);

	// Because we're passing as a reference the id is correct
	return type.getId();
}

int EnemyType::addEnemyType(EnemyType& type) {
	// If the id is already in use try to use the next one
	if (idInUse(type.getId())) {
		CORE_WARN("AddEnemyType: id %d is already in use!", type.getId());
		CORE_WARN("Type to use %d to add", type.getId() + 1);
		type.setId(type.getId() + 1);
		return addEnemyType(type);
	}

	_types.insert(std::map<int, EnemyType>::value_type(type.getId(), type));

	CORE_DEBUG("Created enemy type");
	CORE_DEBUG("\tid: %d", type.getId());
	CORE_DEBUG("\tname: %s", type.getName().c_str());

	return type.getId();
}

////////////////////////////////////////////////////////////////////////////////
// EnemyType static vars
////////////////////////////////////////////////////////////////////////////////

std::map<int, EnemyType> EnemyType::_types;
EnemyType EnemyType::_defaultType(0, "DEFAULT", 4, Stats(), Stats());

////////////////////////////////////////////////////////////////////////////////
// ctor and dtor
////////////////////////////////////////////////////////////////////////////////

EnemyType::EnemyType(int id, const std::string& name, int sides,
		Stats defStats, Stats levelDiff)
	: LuaConfigEntry("EnemyType"),
		_id(id), _name(name), _sides(sides), _defaultStats(defStats),
		_levelDiff(levelDiff) {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void EnemyType::readFromTable(const sol::table& table) {
	_id = table.get<int>("id");
	_name = table.get<std::string>("name");
	_sides = table.get<int>("sides");

	// Temp stats to load from the config
	Stats defStats;
	Stats lvlDiff;

	defStats.readFromTable(table["default_stats"]);
	lvlDiff.readFromTable(table["level_diff_stats"]);

	_defaultStats = defStats;
	_levelDiff = lvlDiff;
}

////////////////////////////////////////////////////////////////////////////////
// Enemy
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Enemy ctor and dtor
////////////////////////////////////////////////////////////////////////////////

Enemy::Enemy(Map* map, float x, float y, int size, EnemyType type)
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

	_lua.lua.set("me", this);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	Unit::draw(target, states);

	sf::CircleShape rng;
	rng.setRadius(getRange());
	rng.setPosition(getX() - (getRange()), getY() - (getRange()));
	rng.setFillColor(sf::Color::Transparent);
	rng.setOutlineColor(sf::Color::Red);
	rng.setOutlineThickness(3.0f);

	target.draw(rng);
}
