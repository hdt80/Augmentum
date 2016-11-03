#include "Projectile.h"

#include "Enemy.h"
#include "Tower.h"
#include "ParticleEmitter.h"
#include "Perk.h"
#include "Common.h"
#include "Unit.h"
#include "Logger.h"
#include "Map.h"
#include "BitWise.h"
#include "GameWindow.h"
#include "Database.h"
#include "Convert.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////

Projectile::Projectile(Map* map, int size, Target* t, Unit* shooter, Color c)
	: Object(map, shooter->getX(), shooter->getY(), shooter->getStats(), size),
		_color(c), _shooter(shooter) {

	// Speed of this Projectile is stored in Tower's projSpeed, not speed
	// so set it to the proper value
	setSpeed(shooter->getProjSpeed());

	_shape.setRadius(size);
	_shape.setFillColor(sf::Color(120, 120, 120));

	// Set the angle we move at towards the enemy
	_direction = (Vector2(t->getX(), t->getY()) - Vector2(x, y)).normalize();

	_shape.setFillColor(c.toSF());
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(-1.0f);

	_b2Box = nullptr;

	b2BodyDef bdf;
	bdf.type = b2_dynamicBody;
	bdf.position.Set(x, y);
	bdf.angle = 0; // Radians
	_b2Box = _map->getWorld()->CreateBody(&bdf);

	b2CircleShape cs;
	cs.m_p.Set(0, 0);
	cs.m_radius = size;

	b2PolygonShape dBox;
	dBox.SetAsBox(size, size);

	b2FixtureDef fd;
	//fd.shape = &cs;
	fd.shape = &dBox;
	fd.density = 1.0f;
	fd.friction = 0.4f;
	fd.isSensor = true;
	_b2Box->CreateFixture(&fd);

	BitWise::bitOn(_objType, ObjectType::PROJECTILE);

	_b2Box->SetUserData(this);
}

Projectile::~Projectile() {}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////

void Projectile::loadLua() {

}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_shape);
}

void Projectile::onCollision(Object* o) {
	// Did we collide with an enemy?
	Enemy* e = dynamic_cast<Enemy*>(o);
	if (e == nullptr) {
		return;
	}
	e->applyDamage(getDamage(), _shooter);

	_shooter->onDamageDealt(getDamage(), e);

	float angle = convert::toDeg((-_direction).angle());

	GameWindow::Emitter.emit(Databases::ParticleDefDatabase.get("hit"),
		getX(), getY(), 50, angle);

	_toRemove = true;
}

void Projectile::move(int diff) {
	updatePosition(getX(), getY());
}

void Projectile::update(int diff) {
	setVelocity(_direction.X * getSpeed(), _direction.Y * getSpeed());
}
