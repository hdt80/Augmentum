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

}

// Set the linear velocity of this Object
// x - X acceleration to apply
// y - Y acceleration to apply
void Object::setVelocity(float x, float y) {
	b2Vec2 vel = _b2Box->GetLinearVelocity();
	CORE_INFO("vel(%g, %g)", vel.x, vel.y);
	b2Vec2 end(x, y);
	CORE_INFO("end(%g, %g)", end.x, end.y);

	b2Vec2 diff = vel - end;
	CORE_INFO("diff (%g, %g)", diff.x, diff.y);
	_b2Box->ApplyLinearImpulseToCenter(diff, true);
}

// Update the Object based on how much time has passed
// diff - How much time has passed, in milliseconds
void Object::update(int diff) {
//	CORE_INFO("pos (%g, %g)", getX(), getY());
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
void Object::setSkillTree(SkillTree* tree) {
	_tree = tree->clone();
	_tree->setAttached(this);
}
