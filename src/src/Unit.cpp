#include "Unit.h"
#include "Map.h"
#include "ExperienceHelper.h"
#include "GameWindow.h"
#include "Database.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor and deconstructor
///////////////////////////////////////////////////////////////////////////////
Unit::Unit()
	: Unit(nullptr, 0, 0, Stats(), 0, 0, sf::Color::Black) {
	
}

Unit::Unit(Map* map, float x, float y, Stats s, int size,
		int sides, sf::Color c)
	: Object(map, x, y, s, size),
		_reload(1), _health(30), _maxHealth(30),
		_hpBar(Vector2(50.0f, 8.0f), sf::Color::Red, sf::Color::Green,
			0, _maxHealth, _health),
		_exp(0.0f),	_prevLevel(-1) {

	// If the stats provided give us a max health set it
	if (s.hasStat("maxHealth")) {
		_maxHealth = s.getStat("maxHealth");
		_health = _maxHealth;
	}
	
	_reload.setMaxCooldown((1 / getFireRate()) * 1000000);

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
	cs.m_radius = getSize();

	b2FixtureDef fd;
	fd.shape = &cs;
	fd.density = 1.0f;
	fd.friction = 0.8f;
	_b2Box->CreateFixture(&fd);

	_b2Box->SetLinearDamping(0.4f);

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

	// Get the max health set by the Stats
	setMaxHealth(getStat("maxHealth"));
	setHealth(getMaxHealth());

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
		p->addObjectTypeOption(ObjectType::PROJECTILE);

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

void Unit::updatePosition(float x, float y) {
	Object::updatePosition(x, y);	

	_hpBar.setPosition(x - getSize(), y - getSize());
}

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
	target.draw(_hpBar);
}

////////////////////////////////////////////////////////////////////////////////
// Health methods
////////////////////////////////////////////////////////////////////////////////

void Unit::applyDamage(float d, Unit* hitter) {
	setHealth(getHealth() - d);

	// If d is negative (a heal) and we go above max health clamp it back
	if (getHealth() > getMaxHealth()) {
		setHealth(getMaxHealth());
	}

	// No health left? Kill this Unit off next update
	if (getHealth() <= 0) {
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
// Health methods
////////////////////////////////////////////////////////////////////////////////

void Unit::setHealth(float f) {
	_health = f;
	_hpBar.setCurrentValue(getHealth());
}

void Unit::setMaxHealth(float f) {
	_maxHealth = f;
	_hpBar.setMaxValue(getMaxHealth());
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
