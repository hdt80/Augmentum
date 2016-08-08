#include "Projectile.h"

#include "Enemy.h"
#include "Tower.h"
#include "ParticleEmitter.h"
#include "Perk.h"
#include "Common.h"

#include "Logger.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
Projectile::Projectile(Map* map, Enemy* e, Tower* t, Color c) :
	Object(map, t->getX(), t->getY(), 1, t->getStats()),
	_color(c), _shooter(t) {

	// Speed of this Projectile is stored in Tower's projSpeed, not speed
	// so set it to the proper value
	setSpeed(t->getProjSpeed());

	_shape.setRadius(PROJECTILE_WIDTH);
	_shape.setFillColor(sf::Color(120, 120, 120));

	// Set the angle we move at towards the enemy
	_direction = (Vector2(e->getX(), e->getY()) - Vector2(x, y)).normalize();
}

Projectile::~Projectile() {}

void Projectile::loadLua() {

}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////
void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_shape);
}

void Projectile::onCollision(Object* o) {
	// Did we collide with an enemy?
	Enemy* e = dynamic_cast<Enemy*>(o);
	if (e == nullptr) {
		return;
	}
	ParticleEmit::emit(x, y, 10, _color);
	e->applyDamage(getDamage(), _shooter);

	_shooter->onDamageDealt(getDamage(), e);

	_toRemove = true;
}

// Overload default Object move, we don't want it to stop ocne we reach the
// target, we want it to keep moving
void Projectile::move(int diff) {
	double deltaMove = (double)getSpeed() * 0.000001f * diff;
	x += _direction.X * deltaMove;
	y += _direction.Y * deltaMove;
}

void Projectile::update(int diff) {
	move(diff);

	_shape.setPosition(getX() - PROJECTILE_WIDTH, getY() - PROJECTILE_WIDTH);
}
