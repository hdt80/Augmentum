#include "Object.h"

#include <string>
#include <algorithm>
#include <cmath>

#include "Logger.h"
#include "Map.h"
#include "Target.h"
#include "Perk.h"
#include "BitWise.h"

#include "util/MathUtil.h"
#include "util/StringUtil.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor and dtor
///////////////////////////////////////////////////////////////////////////////

Object::Object(Map* map, float x, float y, Stats s, int size)
	: Target(x, y),
		_b2Box(nullptr), _map(map), _objType(0),
		_attackerCount(0), _size(size), _baseStats(s), _stats(0.0f),
		_target(nullptr), _toRemove(false) {
	
	setObjectType(ObjectType::DEFAULT);

	updatePosition(x, y);

	if (_b2Box) {
		_b2Box->SetUserData(this);
	}
}

Object::Object()
	: Object(nullptr, 0.0f, 0.0f, Stats(), 20) {

}

Object::~Object() {
	// Deleting a Box2D body by calling the dtor will break a lot of things
	if (_b2Box) {
		_map->getWorld()->DestroyBody(_b2Box);
		_b2Box = nullptr;
	}

	// Make sure we don't delete another Object
	if (_target && _target->isSimpleTarget()) {
		delete _target;
	}

	// Remove all the Perks
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		delete _perks[i];
	}
	_perks.clear();

	_map = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloads
////////////////////////////////////////////////////////////////////////////////

Object::operator std::string() const {
	Vector2 vel = getVelocity();
	return StringUtil::format("Object %x [Pos (%g, %g), Velocity (%g, %g)"
		" ObjType (%d), Size (%g)]", this, getX(), getY(), vel.X, vel.Y,
		_objType, _size);
}

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////

void Object::loadLua() {
	if (_lua.isLoaded()) {
		CORE_WARNING("Setting up a loaded Lua script!");
	}
}

void Object::onCollision(Object* o) {
	//CORE_INFO("%x collided with %x", this, o);
};

void Object::onProjectileHit(Projectile* p) {
	_lua.callFunction("onProjectileHit", p);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onProjectileHit(p);
	}
}

void Object::onUpdate(int diff) {
	_lua.callFunction("onUpdate", diff);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onUpdate(diff);
	}
}

void Object::onMove(int diff) {
	_lua.callFunction("onMove", diff);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onMove(diff);
	}
}

void Object::onShoot(Object* target) {
	CORE_INFO("[Object %x] Shoot to %x", target);
	_lua.callFunction("onShoot", target);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onShoot(target);
	}
}

void Object::onDamageTaken(int dmg, Object* o) {
	CORE_INFO("[Object %x] Took %d dmg from %x", this, dmg ,o);
	_lua.callFunction("onDamageTaken", dmg, o);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onDamageTaken(dmg, o);
	}
}

void Object::onDamageDealt(int dmg, Object* hit) {
	CORE_INFO("[Object %x] Dealt %d dmg to %x", this, dmg, hit);
	_lua.callFunction("onDamageDealt", dmg, hit);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onDamageDealt(dmg, hit);
	}
}

void Object::onDeath() {
	_lua.callFunction("onDeath");
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onDeath();
	}
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}

bool Object::collidesWith(Object* o) const {
	return hasCollision(o);
}

bool Object::contains(float px, float py) const {
	// Use the correct scale
	b2Vec2 vec(MathUtil::toB2(px), MathUtil::toB2(py));
	for (b2Fixture* fix = _b2Box->GetFixtureList(); fix; fix = fix->GetNext()) {
		if (fix->TestPoint(vec)) {
			return true;
		}
	}
	return false;
}

void Object::addCollision(Object* o) {
	_collisions.push_back(o);

	this->onCollision(o);
}

void Object::removeCollision(Object* o) {
	auto it = std::find(_collisions.begin(), _collisions.end(), o);
	if (it != _collisions.end()) {
		_collisions.erase(it);
	}
}

bool Object::hasCollision(Object* o) const {
	return std::find(_collisions.begin(), _collisions.end(), o)
		!= _collisions.end();
}

void Object::move(int diff) {
	updatePosition(getX(), getY());
}

void Object::update(int diff) {
	onUpdate(diff);

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

void Object::setVelocity(float x, float y) {
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

Vector2 Object::getVelocity() const {
	return Vector2(MathUtil::fromB2(_b2Box->GetLinearVelocity().x),
		MathUtil::fromB2(_b2Box->GetLinearVelocity().y));
}

void Object::setPosition(float x, float y) {
	if (!_b2Box) {
		return;
	}
	_b2Box->SetTransform(b2Vec2(MathUtil::toB2(x), MathUtil::toB2(y)),
		_b2Box->GetAngle());

	updatePosition(x, y);
}

float Object::getX() const {
	return MathUtil::fromB2(_b2Box->GetPosition().x);
}

float Object::getY() const {
	return MathUtil::fromB2(_b2Box->GetPosition().y);
}

void Object::updatePosition(float x, float y) {
	if (!_b2Box) {
		return;
	}
	_shape.setPosition(getX() - getSize(), getY() - getSize());
}

void Object::setStats(Stats s, bool relative) {
	if (relative) {
		_baseStats += s;
	} else {
		_baseStats = s;
	}
}

float Object::getStat(const std::string& name) const {
	return _baseStats[name] + _stats[name];
}

void Object::setStat(const std::string& name, float value) {
	_stats[name] = value;
}

void Object::applyStat(Stats s) {
    if (!s.percent) {
        CORE_WARNING("Object::applyStat> Stats isn't percent");
    }
    _stats["range"]     += _baseStats["range"]     * s["range"];
    _stats["fireRate"]  += _baseStats["fireRate"]  * s["fireRate"];
    _stats["damage"]    += _baseStats["damage"]    * s["damage"];
    _stats["projSpeed"] += _baseStats["projSpeed"] * s["projSpeed"];
    _stats["speed"]     += _baseStats["speed"]     * s["speed"];
    _stats["accel"]     += _baseStats["accel"]     * s["accel"];
}

void Object::removePerk(Perk* p) {
	applyStat(-p->getStats());
}

void Object::addPerk(Perk* p) {
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

Perk* Object::getPerk(const std::string& name) const {
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		if (_perks[i]->getName() == name) {
			return _perks[i];
		}
	}
	return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
// Getters and setters
///////////////////////////////////////////////////////////////////////////////

void Object::setObjectType(int type) {
	_objType = type;

	if (!_b2Box) {
		return;
	}

	int allTypes = std::pow((double) 2, ObjectType::COUNT) - 1;

	for (b2Fixture* fix = _b2Box->GetFixtureList(); fix; fix = fix->GetNext()) {
		b2Filter filt = fix->GetFilterData();

		// Category bits - What I am
		filt.categoryBits = type;
		// Mask bits - What I collide with
		filt.maskBits = allTypes & ~type;

		fix->SetFilterData(filt);
	}
}
void Object::addObjectTypeOption(int type) {
	// Take the current object type and set the type bit on
	setObjectType(BitWise::bitOn(getObjectType(), type));
}

bool Object::isObjectTypeOptionSet(int type) {
	return BitWise::bitQuery(getObjectType(), type);
}

void Object::setTarget(Target* t) {
	// Are we already targetting the target?
	if (_target == t) {
		return;
	}

	// If we aren't targetting the same target we check if we need to delete
	// the old target. If it's a simple target we can delete it safely, but if
	// it isn't we will be deleting an object that is in use
	if (_target && _target->isSimpleTarget()) {
		delete _target;
	}

	_target = t;
}

