#ifndef _MAP_H
#define _MAP_H

#include "Path.h"
#include "Tower.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Color.h"

#include <vector>
#include <string>

#define WAVE_DELAY 30 // Time between each wave in seconds
#define MAP_HEALTH 10 // Enemies that can reach the end before you lose

extern bool isEnemy(Object* o);
extern bool isTower(Object* o);
extern bool isProjectile(Object* o);
extern std::string getType(Object* o);

class Map {
public:
	Map();
	~Map();

	void update(int diff);
	void calcCollisions();
	void spawnWave();
	void spawnTower(float x, float y);
	void shoot(Tower* shooter, Projectile* p);

	Path* getPath() { return &_enemyPath; }
	int getHealth() { return _health; }
	int getMaxHealth() { return _maxHealth; }

	void setSize(int w, int h) { _width = w; _height = h;}
	void setHealthRelative(int i) { _health += i; }

	Tower* towerAt(float x, float y);
	bool inMap(Object* o);

	std::vector<Object*> getObjectsInRange(Target* t, float range);
	std::vector<Object*> getObjectsInRange(float x, float y, float range);

	std::vector<Enemy*> getEnemiesInRange(float x, float y, float range);

	std::vector<Object*> objects;

	std::vector<Object*> toRemove;

protected:
	Path _enemyPath; // Path enemies follow

	int _width;
	int _height;

	int _wave;		// Current wave number
	float _waveTime;// Time passed since last wave
	int _waveDelay;	// Time between each wave

	int _health;
	int _maxHealth;
};

#endif
