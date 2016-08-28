#include "Perk.h"

#include "Logger.h"
#include "Convert.h"
#include "Object.h"
#include "Map.h"

////////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
Perk::Perk(std::string name, Stats s, float dur, bool lua, int maxStacks) :
	_name(name), _attached(nullptr), _stats(s), _duration(dur), _maxDuration(dur),
    _stacks(1),	_maxStacks(maxStacks), _stackable(false), _toRemove(false) {

	if (maxStacks > 0) {
		_stackable = true;
	}

	if (lua) {
		_lua.loadScript("./lua/" + name + ".lua");
		loadLua();
	}
}

Perk::~Perk() {
	delete &_stats;
}

Perk* Perk::clone() {
	if (this == nullptr) {
		return nullptr;
	}
	Perk* clone = new Perk(_name, _stats, _maxDuration, _maxStacks);
	clone->setStackable(_stackable);
	return clone;
}

void Perk::loadLua() {
	if (_lua.isLoaded()) {
		CORE_WARNING("[Perk %x] Loading a loaded script [%x]", this, &_lua);
	}

	_lua.lua.set_function("getObjectsInRange", [this](float x, float y, float r) {
		return _attached->getMap()->getObjectsInRange(x, y, r);	
	});

	_lua.lua.set("attached", _attached);
	_lua.lua.set("me", this);
}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////
void Perk::update(int diff) {
	if (_duration <= -1.0f) {
		return;
	}
	_duration -= (diff * 0.000001f);
	if (_duration <= 0.0f) {
		CORE_INFO("[Perk %x] \'%s\' is done", this, getName().c_str());
		_toRemove = true;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Getters and Setters
///////////////////////////////////////////////////////////////////////////////
std::string Perk::getTitle() const {
	return (getName() + "(" + convert::toString(getStacks()) + "/" +
		convert::toString(getMaxStacks()) + ")");
}

void Perk::setStacks(int c) {
    if (c > _maxStacks || c < 0) {
        CORE_INFO("Perk:: c: %i, _maxStacks: %i", c, _maxStacks);
        return;
    }
    if (!_stackable) {
        _duration = _maxDuration;
    } else {
        _stacks = c;
    }
}

void Perk::addStack() {
	if (_stackable && (_stacks < _maxStacks)) {
		++_stacks;
	} else {
        _duration = _maxDuration;
    }
}

void Perk::setAttached(Object* attached) {
	_attached = attached;
	_lua.lua.set("attached", _attached);
}

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////
void Perk::onApply(Object* obj) {
	_lua.callFunction("onApply");
}

void Perk::onUpdate(int diff) {
	_lua.callFunction("onUpdate", diff);
}

void Perk::onMove(int diff) {
	_lua.callFunction("onMove", diff);
}

void Perk::onShoot(Object* target) {
	_lua.callFunction("onShoot", target);
}

void Perk::onDamageDealt(int dmg, Object* hit) {
	_lua.callFunction("onDamageDealt", dmg, hit);
}

void Perk::onDamageTaken(int dmg, Object* attacker) {
	_lua.callFunction("onDamageTaken", dmg, attacker);
}

void Perk::onDeath() {
	_lua.callFunction("onDeath");
}
