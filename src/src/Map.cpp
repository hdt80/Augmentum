#include "Map.h"
#include <string>

#include "Logger.h"
#include "Ship.h"

bool isEnemy(Object* o) { return dynamic_cast<Enemy*>(o) != nullptr; }
bool isTower(Object* o) { return dynamic_cast<Tower*>(o) != nullptr; }
bool isProjectile(Object* o) { return dynamic_cast<Projectile*>(o) != nullptr; }

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
Map::Map() {
	_selected = new Ship(this, 0.0f, 0.0f, 10, Stats());

	objects.push_back(_selected);
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

// The diff is provided in milliseconds
void Map::update(int diff) {
	for (unsigned int i = 0; i < objects.size(); ++i) {
		objects[i]->move(diff);
	}


	for (unsigned int i = 0; i < objects.size(); ++i) {
		objects[i]->update(diff);
		if (objects[i]->isToRemove() || !inMap(objects[i])) {
			// Attacked? Don't remove it, and skip over it. Remove it after
			// no one is attacking it
			if (objects[i]->getAttackerCount() == 0) {
				// Push back before removal or seg faults
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

	calcCollisions();
}

void Map::calcCollisions() {
	for (unsigned int i = 0; i < objects.size(); ++i) {
		// If it's not a projectile it doesn't die on collision
		if (isProjectile(objects[i])) {
			for (unsigned int j = 0; j < objects.size(); ++j) {
				// You can only collide with enemies
				if (isEnemy(objects[j])) {
					if (objects[i]->collidesWith(objects[j])) {
						objects[i]->onCollision(objects[j]);
					}
				}
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

std::vector<Enemy*> Map::getEnemiesInRange(float x, float y, float r) {
	std::vector<Enemy*> objs;	
	for (unsigned int i = 0; i < objects.size(); ++i) {
		if ((objects[i]->distanceWith(x, y) <= r) && isEnemy(objects[i])) {
			objs.push_back(dynamic_cast<Enemy*>(objects[i]));
		}
	}
	return objs;
}

bool Map::inMap(Object* o) {
	return (o->getX() > 0 || o->getX() < _size.X ||
			o->getY() > 0 || o->getY() < _size.Y);
}
