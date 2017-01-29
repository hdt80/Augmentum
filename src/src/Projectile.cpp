#include "Projectile.h"

#include "Enemy.h"
#include "ParticleEmitter.h"
#include "Perk.h"
#include "Common.h"
#include "Unit.h"
#include "Logger.h"
#include "Map.h"
#include "BitWise.h"
#include "GameWindow.h"
#include "Database.h"
#include "util/MathUtil.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////

Projectile::Projectile(Map* map, int size, Target* t, Unit* shoot, sf::Color c)
	: Unit(map, shoot->getX(), shoot->getY(), shoot->getStats(), Stats(0.0f),
			size, 20, sf::Color(96, 96, 96)),
		_color(c), _shooter(shoot) {

	// Speed of this Projectile is stored in Tower's projSpeed, not speed
	// so set it to the proper value
	setSpeed(_shooter->getProjSpeed());

	_shape.setRadius(size);
	_shape.setFillColor(sf::Color(120, 120, 120));

	// Set the angle we move at towards the enemy
	_direction = (Vector2(t->getX(), t->getY()) - Vector2(x, y)).normalize();
	_direction.X = MathUtil::toB2(_direction.X);
	_direction.Y = MathUtil::toB2(_direction.Y);

	_shape.setFillColor(_color);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(-1.0f);

	// If there is already a body destroy it to create the new one
	if (_b2Box) {
		map->getWorld()->DestroyBody(_b2Box);
	}
	_b2Box = nullptr;

	b2BodyDef bdf;
	bdf.type = b2_dynamicBody;
	bdf.position.Set(MathUtil::toB2(x), MathUtil::toB2(y));
	bdf.angle = 0; // Radians
	_b2Box = _map->getWorld()->CreateBody(&bdf);

	b2CircleShape cs;
	cs.m_p.Set(0, 0);
	cs.m_radius = MathUtil::toB2(size / 2);

	b2FixtureDef fd;
	fd.shape = &cs;
	fd.density = 1.0f;
	fd.friction = 0.4f;
	fd.isSensor = true;
	_b2Box->CreateFixture(&fd);

	if (_b2Box) {
		_b2Box->SetUserData(this);
	}

	float speed = MathUtil::toB2(getSpeed());
	setVelocity(_direction.X * speed, _direction.Y * speed);
}

Projectile::~Projectile() {}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Projectile::loadLua() {

}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_shape);
}

void Projectile::onCollision(Object* o) {
	o->onProjectileHit(this);

	float angle = MathUtil::radToDeg((-_direction).angle());

	GameWindow::Emitter.emit(&Databases::ParticleDefDatabase.get("hit"),
		getX(), getY(), 50, angle);

	_toRemove = true;
}

void Projectile::move(int diff) {
	updatePosition(getX(), getY());
}

void Projectile::update(int diff) {
	// No need to convert to b2 units as its done in setVelocity
}
