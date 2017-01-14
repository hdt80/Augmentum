#include "Map.h"

#include <string>
#include <algorithm>

#include "Logger.h"
#include "Ship.h"
#include "Game.h"
#include "environment/Asteroid.h"

////////////////////////////////////////////////////////////////////////////////
// Static methods
////////////////////////////////////////////////////////////////////////////////

Enemy* Map::toEnemy(Object* o) {
	return dynamic_cast<Enemy*>(o);
}

Ship* Map::toShip(Object* o) {
	return dynamic_cast<Ship*>(o);
}

Projectile* Map::toProjectile(Object* o) {
	return dynamic_cast<Projectile*>(o);
}

Unit* Map::toUnit(Object* o) {
	return dynamic_cast<Unit*>(o);
}

Object* Map::toObject(void* o) {
	return (Object*)o;
}

///////////////////////////////////////////////////////////////////////////////
// Constructor and deconstructor
///////////////////////////////////////////////////////////////////////////////

Map::Map()
	: _world(b2Vec2(0.0f, 0.0f)), b2UpdateCounter(0) {

	Stats s;
	s["speed"] = 20.0f;
	s["projSpeed"] = 50.0f;
	_selected = new Ship(this, 0.0f, 0.0f, s, Stats(), 20, 4, sf::Color::Blue);
	_selected->setMaxHealth(30.0f);
	_selected->setObjectType(ObjectType::FRIENDLY);

	objects.push_back(_selected);

	_contactListener = new ContactListener(&_world);

	EnemyType::loadEnemyType("./lua/config.lua");
	EnemyType::loadEnemyType("./lua/et1.lua");

//	CORE_INFO("Distances: ");
//	int level = 0;
//	int prevLevel = -1;
//	Target t(0, 0);
//	for (int i = 0; level < 100; ++i) {
//		level = std::sqrt(t.distanceWith(0, i / 10));
//
//		if (level != prevLevel) {
//			CORE_INFO("Distance %d: %d", i, level);
//			prevLevel = level;
//		}
//	}
}

Map::~Map() {
	for (unsigned int i = 0; i < objects.size(); ++i) {
		delete objects[i];
	}
	objects.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////

void Map::update(int diff) {

	updateBox2D(diff);

	// Move first so the updates follow what the player would see
	for (unsigned int i = 0; i < objects.size(); ++i) {
		objects[i]->move(diff);
	}
	
	// Update all the Objects in the map
	// TODO: Only update the Objects around the player
	for (unsigned int i = 0; i < objects.size(); ++i) {
		objects[i]->update(diff);
		if (objects[i]->isToRemove()) {
			// If this Object is being attacked, and stored as a pointer to
			// the Object attacking the Object being removed. In order to
			// avoid a dangling pointer, we mark the Object for removal instead
			// of deleting it right away
			if (objects[i]->getAttackerCount() == 0) {
				toRemove.push_back(objects[i]);
				objects.erase(objects.begin() + i);
			}
		}
	}

	// Now that all the updating is done we can safely remove all objects
	// that are marked for removal
	for (unsigned int i = 0; i < toRemove.size(); ++i) {
		delete toRemove[i];
	}
	toRemove.clear();
}

void Map::updateBox2D(int diff) {
	// Update Box2D first
	b2UpdateCounter += diff;
	if (b2UpdateCounter >= 16667) {
		// Collision handling is done in here
		_world.Step(b2UpdateCounter / 1000000.0f,
			velocityIterations, positionIterations);
		b2UpdateCounter = 0;
	}
}

std::vector<Object*> Map::getObjectsInRange(Target* t, float r) {
	return getObjectsInRange(t->getX(), t->getY(), r);
}

std::vector<Object*> Map::getObjectsInRange(float x, float y, float r) {
	std::vector<Object*> objs;
	for (Object* o : objects) {
		if (o->distanceWith(x, y) <= r) {
			objs.push_back(o);
		}
	}
	return objs;
}

bool Map::collisionAtPlace(Object* o, float x, float y) {
	return objectAt(o, x, y) != nullptr;
}

void Map::addObject(Object* o) {
	objects.push_back(o);
}

Object* Map::objectAt(Object* o, float x, float y) {
	for (unsigned int i = 0; i < objects.size(); ++i) {
		if (objects[i] != o && objects[i]->contains(x, y)) {
			return objects[i];
		}
	}
	return nullptr;
}

void Map::spawnEnemy(float x, float y, int enemyId, int level) {
	Enemy* e = nullptr;
	if (EnemyType::idInUse(enemyId)) {
		e = new Enemy(this, x, y, 20, *EnemyType::getById(enemyId));	
	} else {
		CORE_WARN("Id %d is not a valid id!", enemyId);
		e = new Enemy(this, x, y, 20, *EnemyType::getDefaultType());
	}

	if (e == nullptr) {
		CORE_ERROR("e is null???");
		return;
	}

	// Level of -1 means scale the Enemy with the distance from (0, 0)
	if (level == -1) {
		level = std::max(1.0f,
			std::sqrt(e->distanceWith(_origin.X, _origin.Y) / 100));
	}

	e->setLevel(level);

	CORE_INFO("Spawning at enemy at (%g, %g), Type: %d, Level: %d",
			x, y, enemyId, level);

	addObject(e);
}

void Map::spawnAsteroid(float x, float y, float radius) {
	Asteroid* ast = new Asteroid(this, x, y, radius);
	addObject(ast);
}

////////////////////////////////////////////////////////////////////////////////
// Debug methods
////////////////////////////////////////////////////////////////////////////////

void Map::dumpObjects() {
	std::stringstream ss;
	for (Object* object : objects) {
		ss << object << ' ';
	}
	CORE_INFO("Objects: %s", ss.str().c_str());
}
