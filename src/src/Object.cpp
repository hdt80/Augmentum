#include "Object.h"

#include "Perk.h"
#include <string>
#include "Logger.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
Object::Object(Map* map, float x, float y, int collRadius, Stats s) :
	Target(x, y), _map(map), _tree(nullptr),  _attackerCount(0), _baseStats(s),
	_target(nullptr), _toRemove(false), _collisionRadius(collRadius) {

}

Object::Object() :
	Target(0, 0), _map(nullptr), _stats(Stats()), _target(nullptr),
	_toRemove(false), _collisionRadius(0) {
}

Object::~Object() {}

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////
void Object::onCollision(Object* o) {
	CORE_INFO("%x collided with %x", this, o);
};

// Load all the functions related to the Object
void Object::loadLua() {
	if (_lua.isLoaded()) {
		CORE_WARNING("Setting up a loaded Lua script!");
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
	_lua.callFunction("onShoot", target);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onShoot(target);
	}
}

void Object::onDamageTaken(int dmg, Object* o) {
	_lua.callFunction("onDamageTaken", dmg, o);
	for (unsigned int i = 0; i < _perks.size(); ++i) {
		_perks[i]->onDamageTaken(dmg, o);
	}
}

void Object::onDamageDealt(int dmg, Object* hit) {
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

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////
void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
}

bool Object::collidesWith(Object* o) {
	return (getCollisionBox().intersects(o->getCollisionBox()));
}

// Returns if a point is within the collision box of an Object
bool Object::contains(float px, float py) {
	return (px >= getX() - _collisionRadius &&
			px <= getX() + _collisionRadius &&
			py >= getY() - _collisionRadius &&
			py <= getY() + _collisionRadius);
}

void Object::move(int diff) {
	// No need to calculate movement if they can't move
	if (getSpeed() <= 0) {
		return;
	}
	// If we don't have anywhere we've moving to don't move
	if (_target == nullptr) {
		_direction = Vector2();
		return;
	}

	Vector2 to(_target->getX(), _target->getY());
	Vector2 cur(x, y);

	Vector2 goingTo(to - cur);
	_direction = goingTo.normalize();

	double deltaMove = (double)getSpeed() * 0.000001f * diff;

	x += _direction.X * deltaMove;
	y += _direction.Y * deltaMove;
}

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

void Object::setStats(Stats s, bool relative) {
	if (relative) {
		_baseStats += s;
	} else {
		_baseStats = s;
	}
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
	applyStat(-*p->getStats());
}

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

void Object::setPosition(float nx, float ny) {
	x = nx;
	y = ny;
	setTarget(nullptr);
}

void Object::moveRelative(float dx, float dy) {
	setPosition(getX() + dx, getY() + dy);
	_shape.setPosition(getX(), getY());
}

void Object::setSkillTree(SkillTree* tree) {
	_tree = tree->clone();
	_tree->setAttached(this);
}
