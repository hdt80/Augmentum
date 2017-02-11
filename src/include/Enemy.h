#ifndef _ENEMY_H
#define _ENEMY_H

#include "Unit.h"
#include "FloatingProgressBar.h"
#include "EnemyType.h"

class Enemy : public Unit {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	Enemy();

	// Enemy ctor
	// map - Map to create this Enemy at
	// x - X coord of the map to create the Enemy at
	// y - Y coord of the map to create the Enemy at
	// size - Size in pixels of this Enemy
	// type - EnemyType this is
	Enemy(Map* map, float x, float y, int size, const EnemyType& type);

	// Enemy dtor
	virtual ~Enemy();

	// Methods /////////////////////////////////////////////////////////////////

	// Load the Lua script used by this Enemy
	void loadLua();

	// Update the enemy depending on its target, updating its coords
	// diff - Milliseconds since last update call
	virtual void update(int diff);

	// A simple target is just an (x, y) coord point. Because an Object
	// isn't just a coord point it isn't a simple target
	virtual bool isSimpleTarget() const { return false; }

	// Get the EnemyType this Enemy uses
	// returns: _enemyType
	inline const EnemyType& getEnemyType() const { return _enemyType; }

	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

protected:
	// Vars ////////////////////////////////////////////////////////////////////

	const EnemyType _enemyType; // Type of this Enemy
};

#endif
