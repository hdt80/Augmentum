#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "Object.h"
#include "Color.h"

class Unit;

class Projectile : public Object {
public:
	// Projectile Ctor
	// map - Map 
	// t - Target to move towards
	// shooter - Who shot this Projectile
	// color - Color to draw the Projectile as
	Projectile(Map* map, Target* t, Unit* shooter, Color c);
	virtual ~Projectile();

	//
	virtual void loadLua();

	// Called when the projectile hits their target
	void onCollision(Object* o);

	void move(int diff);
	void update(int diff);

protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	Color _color;
	Unit* _shooter;
};

#endif
