#include "Unit.h"
#include "Map.h"
#include "ExperienceHelper.h"
#include "GameWindow.h"
#include "Database.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor and deconstructor
///////////////////////////////////////////////////////////////////////////////
Unit::Unit() {}

Unit::Unit(Map* map, float x, float y, Stats s, int size,
		int sides, sf::Color c)
	: Object(map, x, y, s, size),
		_reload(4 * 1000000), _health(30), _maxHealth(30), _exp(0.0f),
		_prevLevel(-1) {

	_shape.setRadius(size);
	_shape.setPointCount(sides);
	_shape.setFillColor(c);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(-3.0f);

	_b2Box = nullptr;

	b2BodyDef bdf;
	bdf.type = b2_dynamicBody;
	bdf.position.Set(x, y);
	bdf.angle = 0; // Radians
	_b2Box = map->getWorld()->CreateBody(&bdf);

	b2CircleShape cs;
	cs.m_p.Set(0, 0);
	cs.m_radius = 20;

	b2PolygonShape dBox;
	dBox.SetAsBox(10.0f, 10.0f);

	b2FixtureDef fd;
	//fd.shape = &cs;
	fd.shape = &dBox;
	fd.density = 1.0f;
	fd.friction = 0.4f;
	_b2Box->CreateFixture(&fd);

	if (_b2Box) {
		_b2Box->SetUserData(this);
	}
}

Unit::~Unit() {}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////

void Unit::onLevelUp() {
	GameWindow::Emitter.emit(Databases::ParticleDefDatabase.get("level_up"),
			getX(), getY(), 500, -1);

	_lua.callFunction("onLevelUp");
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onLevelUp();
	}
}

////////////////////////////////////////////////////////////////////////////////
// Shooting methods
////////////////////////////////////////////////////////////////////////////////

void Unit::shoot(float x, float y) {
	if (_reload.done()) {
		Projectile* p = new Projectile(_map, 5,
				new Target(x, y), this, Color(255, 255, 255, 255));	
		p->setObjectType(getObjectType());

		_map->addObject(p);

		_reload.start();
	} else {
		CORE_WARN("reloading...");
	}
}

void Unit::shoot(Target* target) {
	shoot(target->getX(), target->getY());
}

////////////////////////////////////////////////////////////////////////////////
// Updating methods
////////////////////////////////////////////////////////////////////////////////

void Unit::update(int diff) {
	_reload.update(diff);
	if (getLevel() != _prevLevel) {
		onLevelUp();
		_prevLevel = getLevel();
	}
	Object::update(diff);
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates stats) const {
	target.draw(_shape);
}

////////////////////////////////////////////////////////////////////////////////
// Health methods
////////////////////////////////////////////////////////////////////////////////

void Unit::applyDamage(float d, Unit* hitter) {
	_health += d;

	// If d is negative (a heal) and we go above max health clamp it back
	if (_health > _maxHealth) {
		_health = _maxHealth;
	}

	// No health left? Kill this Unit off next update
	if (_health <= 0) {
		_toRemove = true;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Stat methods
////////////////////////////////////////////////////////////////////////////////

float Unit::getStat(const std::string& name) const {
	// Add the stats gained from the levels
	return _baseStats[name] + (_levelDiff[name] * getLevel()) + _stats[name];
}

////////////////////////////////////////////////////////////////////////////////
// Exp methods
////////////////////////////////////////////////////////////////////////////////

float Unit::getExpForCurrentLevel() const {
	return getExp() - ExperienceHelper::levelToExp(
			ExperienceHelper::expToLevel(getExp()));
}

float Unit::getExpToNextLevel() const {
	return ExperienceHelper::getRemainingExp(_exp);
}

int Unit::getLevel() const {
	return ExperienceHelper::expToLevel(_exp);
}

void Unit::setLevel(int level) {
	_exp = ExperienceHelper::levelToExp(level);
}
