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
	return &getTypes().at(id);
}

bool EnemyType::idInUse(unsigned int id) {
	std::map<int, EnemyType>::iterator it = getTypes().find(id);
	return (it != getTypes().end());
}

int EnemyType::createEnemyType(int id, const std::string& name, int sides,
	Stats defStats, Stats levelDiff) {

	return addEnemyType(EnemyType(id, name, sides, defStats, levelDiff));
}

EnemyType* EnemyType::getDefaultType() {
	static EnemyType* _defaultType
		= new EnemyType(0, "DEFAULT", 4, Stats(), Stats());
	return _defaultType;
}

int EnemyType::loadEnemyType(const std::string& path) {
	// Create a temp EnemyType to load the values into
	EnemyType type(0, "", 0, Stats(), Stats());

	type.readFromFile(path);

	return addEnemyType(type);
}

int EnemyType::addEnemyType(EnemyType type) {
	// If the id is already in use try to use the next one
	if (idInUse(type.getId())) {
		CORE_WARN("AddEnemyType: id %d is already in use!", type.getId());
		CORE_WARN("Type to use %d to add", type.getId() + 1);
		type.setId(type.getId() + 1);
		return addEnemyType(type);
	}

	getTypes().insert(std::map<int, EnemyType>::value_type(type.getId(), type));

	CORE_DEBUG("New enemy type: %s (%d)", type.getName().c_str(), type.getId());

	return type.getId();
}

std::map<int, EnemyType>& EnemyType::getTypes() {
	static std::map<int, EnemyType>* _types = new std::map<int, EnemyType>();
	return *_types;
}

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

	_lua.lua.set("me", this); // Set a reference to this in the lua script
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
