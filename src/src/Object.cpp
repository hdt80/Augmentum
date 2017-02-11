#include "Object.h" 
#include <string>
#include <algorithm>
#include <cmath>

#include "Logger.h"
#include "Map.h"
#include "Projectile.h"
#include "Target.h"
#include "Perk.h"
#include "BitWise.h"

#include "util/MathUtil.h"
#include "util/StringUtil.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor and dtor
///////////////////////////////////////////////////////////////////////////////

Object::Object(Map* map, float x, float y, int size)
	: Target(x, y),
		_b2Box(nullptr), _size(size), _map(map), _objType(0), _toRemove(false) {
	
	setObjectType(ObjectType::DEFAULT);

	updatePosition(x, y);

	if (_b2Box) {
		_b2Box->SetUserData(this);
	}
}

Object::~Object() {
	// Deleting a Box2D body by calling the dtor will break a lot of things
	if (_b2Box) {
		_map->getWorld()->DestroyBody(_b2Box);
		_b2Box = nullptr;
	}

	_map = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}

void Object::loadLua() {
	if (_lua.isLoaded()) {
		CORE_WARNING("Setting up a loaded Lua script!");
	}
}

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////

void Object::onCollision(Object* o) {
	_lua.callFunction("onCollision", o);
};

void Object::onProjectileHit(Projectile* p) {
	_lua.callFunction("onProjectileHit", p);
}

void Object::onUpdate(int diff) {
	_lua.callFunction("onUpdate", diff);
}

void Object::onMove(int diff) {
	_lua.callFunction("onMove", diff);
}

////////////////////////////////////////////////////////////////////////////////
// Update methods
////////////////////////////////////////////////////////////////////////////////

void Object::move(int diff) {
	updatePosition(getX(), getY());
}

void Object::update(int diff) {
	onUpdate(diff);
}

////////////////////////////////////////////////////////////////////////////////
// Object type methods
////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
// Movement methods
////////////////////////////////////////////////////////////////////////////////

void Object::setVelocity(float x, float y) {
	// Don't use acceleration when using an Object
	_b2Box->SetLinearVelocity(b2Vec2(x, y));
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

////////////////////////////////////////////////////////////////////////////////
// Collision methods
////////////////////////////////////////////////////////////////////////////////

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

bool Object::collidesWith(Object* o) const {
	return hasCollision(o);
}
