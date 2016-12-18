#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "Object.h"

class Unit;

class Projectile : public Object {
public:

	// Projectile ctor and dtor ////////////////////////////////////////////////

	// Projectile Ctor
	// map - Map this Projectile is on
	// size - Size in pixels of this Projectile
	// t - Target to move towards
	// shooter - Who shot this Projectile
	// color - Color to draw the Projectile as
	Projectile(Map* map, int size, Target* t, Unit* shooter, sf::Color c);

	// Projectile dtor
	virtual ~Projectile();

	// Methods /////////////////////////////////////////////////////////////////

	// Load the Lua script associated with this Projectile
	virtual void loadLua();

	// Called when the projectile hits their target
	// o - Object collided with
	void onCollision(Object* o);

	//
	void move(int diff);
	void update(int diff);

protected:

	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	sf::Color _color; // Color to draw this Projectile as
	Unit* _shooter; // Who shot this Projectile
};

#endif
