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

	_selected = new Ship(this, 0.0f, 0.0f, Stats(), 4, sf::Color::Blue);

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

	_world.Step(1.0f / 60.0f, velocityIterations, positionIterations);

	// Calculate the collisions after all the removal and moves so the player
	// gets accurate feedback and isn't behind a frame
	calcCollisions();
}

// Calculate all the collisions on the Map and call the collision events
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

// Get all Objects near a Target
// t - Target to check
// r - Radius, how close the Object must be to be included
std::vector<Object*> Map::getObjectsInRange(Target* t, float r) {
	return getObjectsInRange(t->getX(), t->getY(), r);
}

// Get all Objects near a Target
// x - X coord to check
// y - Y coord to check
// r - Radius, how close the Object must be to be included
std::vector<Object*> Map::getObjectsInRange(float x, float y, float r) {
	std::vector<Object*> objs;
	for (unsigned int i = 0; i < objects.size(); ++i) {
		if (objects[i]->distanceWith(x, y) <= r) {
			objs.push_back(objects[i]);
		}
	}
	return objs;
}

// Check if a BoundBox intersects with any other BoundBox
// o - Object to ignore during checks, use nullptr to check all objects
// box - Box to check the collision with
bool Map::collisionAtPlace(Object* o, BoundBox* box) const {
	// No bound box? can't have a collision
	// TODO: Temp code to test Box2d
	return false;
	if (box == nullptr) {
		return false;
	}

	for (Object* obj : objects) {
		if (obj != o && box->intersects(obj->getBoundBox())) {
			return true;
		}
	}

	return false;
}

// Check if there is a collision at the position
// o - Object to ignore, or use nullptr to check all objects
// x - x coord to check
// y - y coord to check
bool Map::collisionAtPlace(Object* o, float x, float y) {
	// TODO: Temp code to test Box2d
	return false;
	return (objectAt(o, x, y) != nullptr);
}

// Return the Object at (x, y), or nullptr if no object is there
// o - Object to ignore, use nullptr to check for all objects
// x - X coord of the point
// y - Y coord of the point
Object* Map::objectAt(Object* o, float x, float y) {
	for (unsigned int i = 0; i < objects.size(); ++i) {
		if (objects[i] != o && objects[i]->contains(x, y)) {
			return objects[i];
		}
	}
	return nullptr;
}
