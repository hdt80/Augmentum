#include "game/Map.h"

#include "game/Ship.h"
#include "game/Game.h"
#include "game/Databases.h"
#include "game/environment/Asteroid.h"
#include "game/ContactListener.h"
#include "game/Object.h"
#include "game/Enemy.h"
#include "game/Projectile.h"

#include "logger/Logger.h"

#include <string>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
// Constructor and deconstructor
///////////////////////////////////////////////////////////////////////////////

Map::Map()
	: _world(b2Vec2(0.0f, 0.0f)), b2UpdateCounter(0), _gameOver(false) {

	reset();

	_contactListener = new ContactListener(&_world);

//	AG_INFO("Distances: ");
//	int level = 0;
//	int prevLevel = -1;
//	Target t(0, 0);
//	for (int i = 0; level < 100; ++i) {
//		level = std::sqrt(t.distanceWith(0, i / 10));
//
//		if (level != prevLevel) {
//			AG_INFO("Distance %d: %d", i, level);
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
			toRemove.push_back(objects[i]);
			objects.erase(objects.begin() + i);
		}
	}

	if (_selected->isToRemove()) {
		setGameOver(true);
	}

	// Now that all the updating is done we can safely remove all objects
	// that are marked for removal
	for (unsigned int i = 0; i < toRemove.size(); ++i) {
		delete toRemove[i];
	}
	toRemove.clear();
}

void Map::updateBox2D(int diff) {
	b2UpdateCounter += diff;
	// Only update Box2D at 60 times per second
	if (b2UpdateCounter >= 16667) {
		// Collision handling is done in here
		_world.Step(b2UpdateCounter / 1000000.0f,
			velocityIterations, positionIterations);
		b2UpdateCounter = 0;
	}
}

void Map::reset() {
	for (Object* obj : objects) {
		delete obj;
	}
	objects.clear();
	_selected = nullptr;

	Stats s;
	s["speed"] = 20.0f;
	s["projSpeed"] = 50.0f;
	s["accel"] = 0.4;
	_selected = new Ship(this, 0.0f, 0.0f, s, Stats(), 20, 4, sf::Color::Blue);
	_selected->setMaxHealth(30.0f);
	_selected->setObjectType(ObjectType::FRIENDLY);
	_selected->setSkillTree(SkillTrees::basicTree);

	addObject(_selected);

	setGameOver(false);
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

void Map::spawnEnemy(float x, float y, const std::string& id, int level) {
	Enemy* e = nullptr;
	if (Databases::EnemyTypes.has(id)) {
		e = new Enemy(this, x, y, 20, Databases::EnemyTypes.get(id));
	} else {
		AG_WARN("Id %s is not a valid id!", id.c_str());
		e = new Enemy(this, x, y, 20, Databases::EnemyTypes.getDefault());
	}

	if (e == nullptr) {
		AG_ERROR("e is null???");
		return;
	}

	// Level of -1 means scale the Enemy with the distance from (0, 0)
	if (level == -1) {
		level = std::max(1.0f,
			std::sqrt(e->distanceWith(_origin.X, _origin.Y) / 100));
	}

	e->setLevel(level);

	AG_INFO("Spawning at enemy at (%g, %g), Type: %d, Level: %d",
		x, y, id.c_str(), level);

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
	AG_INFO("Objects: %s", ss.str().c_str());
}
