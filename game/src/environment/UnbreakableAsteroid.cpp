#include "game/environment/UnbreakableAsteroid.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

UnbreakableAsteroid::UnbreakableAsteroid(Map* map, float x, float y,
	float maxRadius)
	: Asteroid(map, x, y, maxRadius) {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////

void UnbreakableAsteroid::onProjectileHit(Projectile* proj) {
	// Don't allow any damage to be dealt to this UnbreakableAsteroid
}
