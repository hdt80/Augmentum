#include "Object.h"

#include <string>
#include <algorithm>
#include <cmath>
#include "Logger.h"
#include "Map.h"
#include "Target.h"
#include "Perk.h"
#include "bounds/RectangleBoundBox.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
Object::Object(Map* map, float x, float y, Stats s)
	: Target(x, y),
		_boundBox(nullptr),	_map(map), _tree(nullptr),  _attackerCount(0),
		_baseStats(s), _target(nullptr), _toRemove(false) {
	
}

Object::Object()
	: Object(nullptr, 0.0f, 0.0f, Stats()) {
}

// Object dtor
Object::~Object() {
	if (_b2Box) {
		_map->getWorld()->DestroyBody(_b2Box);
	}

	delete _boundBox;
	delete _tree;

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
// Events
////////////////////////////////////////////////////////////////////////////////

//
void Object::onCollision(Object* o) {
	//CORE_INFO("%x collided with %x", this, o);
};

void Object::BeginContact(b2Contact* contact) {
	CORE_INFO("[Object %x] BeginContact", this);
}

void Object::EndContact(b2Contact* contact) {
	CORE_INFO("[Object %x] EndContact", this);
}

void Object::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	CORE_INFO("[Object %x] PreSolve", this);
}

void Object::PostSolve(b2Contact* contact, const b2Manifold* newManifold) {
	CORE_INFO("[Object %x] PostSolve", this);
}

// Load all the functions related to the Object
void Object::loadLua() {
	if (_lua.isLoaded()) {
		CORE_WARNING("Setting up a loaded Lua script!");
	}
}

//
void Object::onUpdate(int diff) {
	_lua.callFunction("onUpdate", diff);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onUpdate(diff);
	}
}

//
void Object::onMove(int diff) {
	_lua.callFunction("onMove", diff);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onMove(diff);
	}
}

//
void Object::onShoot(Object* target) {
	_lua.callFunction("onShoot", target);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onShoot(target);
	}
}

//
void Object::onDamageTaken(int dmg, Object* o) {
	_lua.callFunction("onDamageTaken", dmg, o);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onDamageTaken(dmg, o);
	}
}

//
void Object::onDamageDealt(int dmg, Object* hit) {
	_lua.callFunction("onDamageDealt", dmg, hit);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onDamageDealt(dmg, hit);
	}
}

//
void Object::onDeath() {
	_lua.callFunction("onDeath");
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onDeath();
	}
}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////

//
void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}

// Check if another Object collides with this one
// o - Object to check collision with
bool Object::collidesWith(Object* o) const {
	// TODO: Temp code to test Box2d
	return false;
	// No bound box? No collisions possible
	if (_boundBox == nullptr || o->getBoundBox() == nullptr) {
		return false;
	}

	return (o->intersectsWith(getBoundBox()));
}

// Returns if a point is within the collision box of an Object
// px - X coord to check
// py - Y coord to check
bool Object::contains(float px, float py) const {
	// TODO: Temp code to test Box2d
	return false;
	// No bound box? No collisions possible
	if (_boundBox == nullptr) {
		return false;
	}
	return getBoundBox()->contains(px, py);
}

// Check if a BoundBox intersects with our BoundBox
// box - BoundBox to check with
bool Object::intersectsWith(BoundBox* box) const {
	// TODO: Temp code to test Box2d
	return false;
	// No bound box? No collisions possible
	if (_boundBox == nullptr || box == nullptr) {
		return false;
	}
	return getBoundBox()->intersects(box);	
}

// Move where this Object will be next update
// diff - Milliseconds that have passed since the last update
void Object::move(int diff) {
	// No need to calculate movement if they can't move
	if (getSpeed() <= 0) {
		return;
	}

	//Vector2 to(_target->getX(), _target->getY());
	//Vector2 cur(x, y);

	//Vector2 goingTo(to - cur);
	//_direction = goingTo.normalize();

	double deltaMove = (double)getSpeed() * 0.000001f * diff;

	_velocity.X = approach(_velocityGoal.X, _velocity.X, deltaMove);
	_velocity.Y = approach(_velocityGoal.Y, _velocity.Y, deltaMove);

	float newX = x + _velocity.X;
	float newY = y + _velocity.Y;

	// Check each direction of travel for collision
	if (_boundBox) {
		// Check collision on the X plane
		_boundBox->setOrigin(newX, y);
		if (!_map->collisionAtPlace(this, _boundBox)) {
			x = newX;	
		} else {
			_velocity.X = 0.0f;
		}

		// Check collision on the Y place
		_boundBox->setOrigin(x, newY);
		if (!_map->collisionAtPlace(this, _boundBox)) {
			y = newY;	
		} else {
			_velocity.Y = 0.0f;
		}

		// After we check each direction, move to the boundbox to the new place
	}

	setPosition(x, y);
}

// Update the Object based on how much time has passed
// diff - How much time has passed, in milliseconds
void Object::update(int diff) {
	onUpdate(diff);

	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->update(diff);
		if (_perks[i]->isToRemove()) {
			removePerk(_perks[i]);
			_perks.erase(_perks.begin() + i);
		}
	}
}

//
void Object::setStats(Stats s, bool relative) {
	if (relative) {
		_baseStats += s;
	} else {
		_baseStats = s;
	}
}

//
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

//
void Object::removePerk(Perk* p) {
	applyStat(-*p->getStats());
}

//
void Object::addPerk(Perk* p) {
	// If we already have the buff
	if (getPerk(p->getName()) != nullptr) {
		Perk* curP = getPerk(p->getName());
		curP->setAttached(this);

		// Stackable and we can add a stack? Apply stat change and add 1 stack
		if (p->isStackable() && (curP->getStacks() < curP->getMaxStacks())) {
			// Add the stat mod to the current perk so removal is correct
			*curP->getStats() += *p->getStats();
			curP->addStack();
			applyStat(*p->getStats());
		}
		// Reset duration
		curP->setDuration(p->getDuration());
	} else {
		p->setAttached(this);
		_perks.push_back(p);
		applyStat(*p->getStats());
	}
}

//
Perk* Object::getPerk(std::string name) {
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

//
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

//
void Object::setPosition(float nx, float ny) {
	x = nx;
	y = ny;

	_b2Box->SetTransform(b2Vec2(x, y), _b2Box->GetAngle());
	_shape.setPosition(x, y);
	_boundBox->setOrigin(x, y);
}

// Linear interpolation
// max - Max value to approach
// cur - Current value
// dt - Delta time (milliseconds) How much to advance the value
float Object::approach(float max, float cur, float dt) {
	float diff = max - cur;

	if (diff > dt) {
		return cur + dt;
	}
	if (diff < -dt) {
		return cur - dt;
	}

	return max;
}

//
void Object::setVelocity(float x, float y) {
	_velocityGoal.X = x;
	_velocityGoal.Y = y;
}

//
void Object::moveRelative(float dx, float dy) {
	setPosition(getX() + dx, getY() + dy);
	_shape.setPosition(getX(), getY());
}

//
void Object::setSkillTree(SkillTree* tree) {
	_tree = tree->clone();
	_tree->setAttached(this);
}
