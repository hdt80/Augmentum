#include "Unit.h"

#include "Map.h"
#include "Projectile.h"
#include "ExperienceHelper.h"
#include "GameWindow.h"
#include "Databases.h"

#include "util/MathUtil.h"
#include "util/ObjectUtil.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor and deconstructor
////////////////////////////////////////////////////////////////////////////////

Unit::Unit(Map* map, float x, float y, Stats s, Stats lvlDiff,
		int size, int sides, sf::Color c)
	: Entity(map, x, y, size, 1),
		_reload(1), _levelDiff(lvlDiff),
		_exp(0.0f),	_prevLevel(-1), _tree(nullptr) {

	if (sides < 3 || sides > 8) {
		CORE_WARN("Cannot have %d sides. Wrapping to valid values", sides);
		if (sides < 3) {
			sides = 3;
		} else {
			sides = 8;
		}
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

	// Convert the points into B2's scale
	std::vector<b2Vec2> b2Points(points.size());
	for (unsigned int i = 0; i < points.size(); ++i) {
		b2Points[i] =
			b2Vec2(MathUtil::toB2(points[i].x), MathUtil::toB2(points[i].y));
	}
	b2PolygonShape ps;
	ps.Set(&b2Points[0], points.size());

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

	// Remove all the Perks
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		delete _perks[i];
	}
	_perks.clear();
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////

void Unit::onProjectileHit(Projectile* p) {
	dealDamage(p->getDamage(), p->getShooter());
}

void Unit::onLevelUp() {
	GameWindow::Emitter.emit(&Databases::ParticleDefs.get("level_up"),
		getX(), getY(), 500, -1);

	// Get the max health set by the Stats
	setMaxHealth(getStat("maxHealth"));
	setHealth(getMaxHealth());

	_lua.callFunction("onLevelUp");
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onLevelUp(getLevel());
	}
}

void Unit::onEntityKilled(Entity* killed) {
	_lua.callFunction("onUnitKill");
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onEntityKilled(killed);
	}

	Unit* unit = nullptr;
	if ((unit = ObjectUtil::toType<Unit>(unit))) {
			addExp(unit->getLevel());
	}
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

////////////////////////////////////////////////////////////////////////////////
// Updating methods
////////////////////////////////////////////////////////////////////////////////

void Unit::setVelocity(float x, float y) {
	b2Vec2 vel = _b2Box->GetLinearVelocity();

	// The speed stat isn't scaled to Box2D because the movement is noticed
	// in the game scale, so scaling down the speed would be very noticable
	b2Vec2 end(MathUtil::toB2(x) * getSpeed(), MathUtil::toB2(y) * getSpeed());

	// Diff the velocity needs to change to reach the wanted velocity
	b2Vec2 diff = end - vel;

	// If there is a value in the diff, that means that a movement will occur,
	// so only bother to apply acceleration and the force if there will be one
	if (diff.x != 0.0f || diff.y != 0.0f) {
		// The accel stat is a percent increase
		diff *= (1 + MathUtil::toB2(getAccel()));
		_b2Box->ApplyLinearImpulseToCenter(diff, true);
	}
}

void Unit::update(int diff) {
	Entity::update(diff);

	_reload.update(diff);

	if (getLevel() != _prevLevel) {
		onLevelUp();
		_prevLevel = getLevel();
	}
	
	// Update each perk
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->update(diff);
		// If the perk has timed out or removed by another perk remove it
		if (_perks[i]->isToRemove()) {
			removePerk(_perks[i]);
			_perks.erase(_perks.begin() + i);
		}
	}
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates stats) const {
	target.draw(_shape);
	target.draw(_hpBar);
}

////////////////////////////////////////////////////////////////////////////////
// Stat methods
////////////////////////////////////////////////////////////////////////////////

float Unit::getStat(const std::string& name) const {
	// Add the stats gained from the levels
	return _baseStats[name] + (_levelDiff[name] * getLevel()) + _statMods[name];
}

void Unit::setStats(Stats s, bool relative) {
	if (relative) {
		_baseStats += s;
	} else {
		_baseStats = s;
	}
}

void Unit::setStat(const std::string& name, float value) {
	_statMods[name] = value;
}

void Unit::applyStat(Stats s) {
    if (!s.percent) {
        CORE_WARNING("Object::applyStat> Stats isn't percent");
    }
    _statMods["range"]     += _baseStats["range"]     * s["range"];
    _statMods["fireRate"]  += _baseStats["fireRate"]  * s["fireRate"];
    _statMods["damage"]    += _baseStats["damage"]    * s["damage"];
    _statMods["projSpeed"] += _baseStats["projSpeed"] * s["projSpeed"];
    _statMods["speed"]     += _baseStats["speed"]     * s["speed"];
    _statMods["accel"]     += _baseStats["accel"]     * s["accel"];
}

void Unit::removePerk(Perk* p) {
	applyStat(-p->getStats());
}

void Unit::addPerk(Perk* p) {
	// If we already have the buff
	if (getPerk(p->getName()) != nullptr) {
		Perk* curP = getPerk(p->getName());
		curP->setAttached(this);

		// Stackable and we can add a stack? Apply stat change and add 1 stack
		if (p->isStackable() && (curP->getStacks() < curP->getMaxStacks())) {
			// Add the stat mod to the current perk so removal is correct
			curP->getStats() += p->getStats();
			curP->addStack();
			applyStat(p->getStats());
		}
		// Reset duration
		curP->setDuration(p->getDuration());
	} else {
		p->setAttached(this);
		_perks.push_back(p);
		applyStat(p->getStats());
	}
}

Perk* Unit::getPerk(const std::string& name) const {
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		if (_perks[i]->getName() == name) {
			return _perks[i];
		}
	}
	return nullptr;
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
