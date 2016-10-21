#include "Map.h"
#include <string>

#include "Logger.h"
#include "Ship.h"

bool isEnemy(Object* o) { return dynamic_cast<Enemy*>(o) != nullptr; }
bool isTower(Object* o) { return dynamic_cast<Tower*>(o) != nullptr; }
bool isProjectile(Object* o) { return dynamic_cast<Projectile*>(o) != nullptr; }

// String representation of an Object
std::string getType(Object* o) {
	if (isEnemy(o)) {
		return "Enemy";
	} else if (isProjectile(o)) {
		return "Projectile";
	} else if (isTower(o)) {
		return "Tower";
	} else {
		return "Object (Unknown)";
	}
}

///////////////////////////////////////////////////////////////////////////////
// Constructor and deconstructor
///////////////////////////////////////////////////////////////////////////////

Map::Map()
		: _world(b2Vec2(0.0f, 0.0f)) {

	Stats s;
	s["speed"] = 20.0f;
	s["projSpeed"] = 50.0f;
	_selected = new Ship(this, 0.0f, 0.0f, s, 4, sf::Color::Blue);
	_selected->setMaxHealth(30.0f);
	_selected->setObjectType(ObjectType::FRIENDLY);

	objects.push_back(_selected);

	_contactListener = new ContactListener(&_world);
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

	b2UpdateCounter += diff;
	if (b2UpdateCounter >= 16667) {
		_world.Step(b2UpdateCounter / 1000000.0f,
				velocityIterations, positionIterations);
		b2UpdateCounter = 0;
	}

	// Calculate the collisions after all the removal and moves so the player
	// gets accurate feedback and isn't behind a frame
	calcCollisions();
}

void Map::calcCollisions() {
	for (unsigned int i = 0; i < objects.size(); ++i) {
		for (unsigned int j = 0; j < objects.size(); ++j) {
			// Ensure that we aren't checking with ourself
			if (objects[i] != objects[j] &&
					objects[i]->collidesWith(objects[j])) {
				objects[i]->onCollision(objects[j]);
			}
		}
	}
}

std::vector<Object*> Map::getObjectsInRange(Target* t, float r) {
	return getObjectsInRange(t->getX(), t->getY(), r);
}

std::vector<Object*> Map::getObjectsInRange(float x, float y, float r) {
	std::vector<Object*> objs;
	for (unsigned int i = 0; i < objects.size(); ++i) {
		if (objects[i]->distanceWith(x, y) <= r) {
			objs.push_back(objects[i]);
		}
	}
	return objs;
}

bool Map::collisionAtPlace(Object* o, float x, float y) {
	// TODO: Temp code to test Box2d
	return false;
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
