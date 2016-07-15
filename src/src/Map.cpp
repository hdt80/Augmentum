#include "Map.h"
#include <string>

#include "Logger.h"

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
Map::Map() : _wave(0), _waveTime(0), _waveDelay(WAVE_DELAY),
	_health(MAP_HEALTH), _maxHealth(_health) {

	_enemyPath.addPoint(0, 50);
	_enemyPath.addPoint(50, 50);
	_enemyPath.addPoint(50, 400);
	_enemyPath.addPoint(400, 400);

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
	//CORE_INFO("Diff: %fs | waveTime: %fs", diff * 0.000001f, _waveTime);
	if (_waveTime >= _waveDelay) {
		spawnWave();
		_waveTime = 0;
	}
	_waveTime += diff * 0.000001f;

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

// Spawn a new wave
void Map::spawnWave() { 
	CORE_INFO("Spawning wave %i", ++_wave);
	Stats enemyStats;
	enemyStats["speed"] = 50;
	objects.push_back(new Enemy(this, 10.0f, enemyStats, &_enemyPath, 20));
}

// Spawn a tower at (x, y)
void Map::spawnTower(float x, float y) {
	CORE_INFO("Spawning tower at (%g, %g)", x, y);
	Stats towerStats;
	towerStats["range"] = 200;
	towerStats["fireRate"] = 1.0f;
	towerStats["damage"] = 1.0f;
	towerStats["speed"] = 0.0f;
	towerStats["projSpeed"] = 500.0f;
	Tower* t = new Tower(this, x, y, towerStats);
	t->setSkillTree(SkillTrees::basicTree);
	objects.push_back(t);
}

// Return the Object at (x, y)
// If no Object is there return nullptr 
Tower* Map::towerAt(float x, float y) {
	for (unsigned int i = 0; i < objects.size(); ++i) {
		if (objects[i]->contains(x, y) && isTower(objects[i])) {
			return dynamic_cast<Tower*>(objects[i]);
		}
	}
	return nullptr;
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
	return (o->getX() > 0 || o->getX() < _width ||
			o->getY() > 0 || o->getY() < _height);
}

// Tower t is shooting at e, so spawn a projectile and begin tracking it
void Map::shoot(Tower* t, Projectile* p) {
	objects.push_back(p);
}
