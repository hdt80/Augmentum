#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "Object.h"
#include "Color.h"

class Tower;
class Enemy;

class Projectile : public Object {
public:
	Projectile(Map* map, Enemy* e, Tower* t, Color c);
	virtual ~Projectile();

	virtual void loadLua();

	// Called when the projectile hits their target
	void onCollision(Object* o);

	sf::FloatRect getCollisionBox() { return _shape.getGlobalBounds(); }

	void move(int diff);
	void update(int diff);
protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	Color _color;
	Tower* _shooter; // Tower shot from
};

#endif
