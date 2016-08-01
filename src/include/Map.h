#ifndef _MAP_H
#define _MAP_H

#include "Tower.h"
#include "Enemy.h"
#include "Projectile.h"

#include <vector>
#include <string>

extern bool isEnemy(Object* o);
extern bool isTower(Object* o);
extern bool isProjectile(Object* o);
extern std::string getType(Object* o);

class Ship;

class Map {
public:
	Map();
	~Map();

	void update(int diff);
	void calcCollisions();

	void setSize(int w, int h) { _size.X = w; _size.Y = h;}

	// If the Object is within the bounds of this Map
	bool inMap(Object* o);

	Ship* getSelected() { return _selected; }

	// Get all Objects within a radius of a point
	std::vector<Object*> getObjectsInRange(Target* t, float range);
	std::vector<Object*> getObjectsInRange(float x, float y, float range);
	std::vector<Enemy*> getEnemiesInRange(float x, float y, float range);

	// All the Objects that exist in the world
	std::vector<Object*> objects;

	// Object marked for removal
	std::vector<Object*> toRemove;

protected:
	Vector2 _size;
	Vector2 _origin; // (0, 0)

	Ship* _selected;
};

#endif
