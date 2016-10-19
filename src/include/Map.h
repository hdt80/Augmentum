#ifndef _MAP_H
#define _MAP_H

#include "Object.h"
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"
#include "ContactListener.h"

#include <vector>
#include <string>

#include "Box2D/Box2D.h"

extern bool isEnemy(Object* o);
extern bool isTower(Object* o);
extern bool isProjectile(Object* o);
extern std::string getType(Object* o);

class Ship;

class Map {
public:
	Map();
	~Map();

	// Simulate the Map
	// diff - Microseconds to simulate the Map for
	void update(int diff);

	// Calculate all the collisions between all the Objects in this Map
	void calcCollisions();

	// Get the Ship the player is using
	// returns: Pointer to the ship the player controls
	Ship* getSelected() { return _selected; }

	// Get the Box2D world used by this Map
	// returns: Point to the b2World used for the physics simulations
	b2World* getWorld() { return &_world; }

	// Get all Objects within a radius of a point
	
	// Get all the Objects within a radius of a point
	// t - Point to find the Objects of
	// range - Radius to look around
	std::vector<Object*> getObjectsInRange(Target* t, float range);

	// Get all the Objects within a radius of a point
	// x - X coord of the world
	// y - Y coord of the world
	// range - Radius to look around
	std::vector<Object*> getObjectsInRange(float x, float y, float range);

	// Check if a collision at the point (x, y), ignoring Object o
	// o - Object to ignore during checks
	// x - X coord to check for a collision
	// y - Y coord to check for a collision
	bool collisionAtPlace(Object* o, float x, float y);

	// Return the Object at (x, y), ignoring Object o
	Object* objectAt(Object* o, float x, float y);

	// All the Objects that exist in the world
	std::vector<Object*> objects;

	// Object marked for removal
	std::vector<Object*> toRemove;

protected:
	Vector2 _origin; // (0, 0)

	Ship* _selected; // Ship the player is controlling

	b2World _world;
	ContactListener* _contactListener;

	// How many times to iterate the world
	int velocityIterations = 6;
	int positionIterations = 2;

	float b2UpdateCounter; // Ensure that the b2 world is only updated 60/sec
};

#endif
