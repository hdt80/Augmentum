#include "Unit.h"
#include "Map.h"
#include "ExperienceHelper.h"
#include "GameWindow.h"
#include "Database.h"
#include "util/MathUtil.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor and deconstructor
///////////////////////////////////////////////////////////////////////////////
Unit::Unit()
	: Unit(nullptr, 0, 0, Stats(), Stats(), 0, 0, sf::Color::Black) {
	
}

Unit::Unit(Map* map, float x, float y, Stats s, Stats lvlDiff,
		int size, int sides, sf::Color c)
	: Object(map, x, y, s, size),
		_reload(1), _levelDiff(lvlDiff), _health(30), _maxHealth(30),
		_hpBar(Vector2(50.0f, 8.0f), sf::Color::Red, sf::Color::Green,
			0, _maxHealth, _health),
		_exp(0.0f),	_prevLevel(-1), _tree(nullptr) {

	if (sides < 3) {
		CORE_WARN("Cannot have sides be less than 3. Setting to 3");
		sides = 3;
	}

	// If the stats provided give us a max health set it
	if (s.hasStat("maxHealth")) {
		_maxHealth = s.getStat("maxHealth");
		_health = _maxHealth;
	}
	
	// Cooldowns are counted in microseconds
	_reload.setMaxCooldown((1 / getFireRate()) * 1000000);

	// Set up the shape
	_shape.setRadius(size);
	_shape.setPointCount(sides);
	_shape.setFillColor(c);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(-3.0f);

	if (_b2Box) {
		map->getWorld()->DestroyBody(_b2Box);
	}
	_b2Box = nullptr;

	b2BodyDef bdf;
	bdf.type = b2_dynamicBody;
	bdf.position.Set(MathUtil::toB2(x), MathUtil::toB2(y));
	bdf.angle = 0; // Radians
	bdf.fixedRotation = true; // Prevent rotaton
	_b2Box = map->getWorld()->CreateBody(&bdf);

	std::vector<b2Vec2> points = MathUtil::generatePolygon(sides, size);
	std::vector<b2Vec2> b2Points(size);
	for (unsigned int i = 0; i < points.size(); ++i) {
		b2Points[i] = 
			b2Vec2(MathUtil::toB2(points[i].x), MathUtil::toB2(points[i].y));
	}
	b2PolygonShape ps;
	ps.Set(&b2Points[0], sides);

	// Fixture definition of this Unit
	b2FixtureDef fd;
	fd.shape = &ps; // Set the shape we use
	fd.density = 1.0f;
	//fd.friction = 0.1f; // Have some accel and deccel
	fd.restitution = 1.0f; // Bounce completely off other b2 objects
	_b2Box->CreateFixture(&fd);

	_b2Box->SetLinearDamping(0.1f);
	_b2Box->SetUserData(this);
}

Unit::~Unit() {
	if (_tree) {
		delete _tree;
	}

	// Deleting a Box2D body by calling the dtor will break a lot of things
	if (_b2Box) {
		_map->getWorld()->DestroyBody(_b2Box);
		_b2Box = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////

void Unit::onProjectileHit(Projectile* p) {
	applyDamage(p->getDamage(), p->getShooter());
}

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

void Unit::onUnitKill(Unit* killed) {
	CORE_INFO("[Unit %x] Killed %x", this, killed);
	_lua.callFunction("onUnitKill");
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onUnitKill(killed);
	}

	addExp(killed->getLevel());
}

////////////////////////////////////////////////////////////////////////////////
// Shooting methods
////////////////////////////////////////////////////////////////////////////////

void Unit::shoot(float x, float y) {
	if (_reload.done()) {
		Projectile* p = new Projectile(_map, 5,
				new Target(x, y), this, sf::Color::White);	
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

	onDamageTaken(d, hitter);

	// No health left? Kill this Unit off next update
	if (getHealth() <= 0) {
		_toRemove = true;
		hitter->onUnitKill(this);
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

void Unit::setSkillTree(SkillTree* tree) {
	_tree = tree->clone();
	_tree->setAttached(this);
}
