#pragma once

#include "game/environment/Asteroid.h"

class UnbreakableAsteroid : public Asteroid {
public:	
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// UnbreakableAsteroid ctor
	// map - Map this Asteroid exists on
	// x - X coord of the world to spawn the Asteroid on
	// y - Y coord of the world to spawn the Asteroid on
	// maxRadius - Max size this Asteroid can be
	UnbreakableAsteroid(Map* map, float x, float y, float maxRadius);

	// Methods /////////////////////////////////////////////////////////////////
	
	// Events //////////////////////////////////////////////////////////////////
	
	// Occurs when this Unit is hit by a Projectile
	void onProjectileHit(Projectile* proj);
	
protected:
};
