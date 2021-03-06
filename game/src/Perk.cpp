#include "game/Perk.h"

#include "game/Object.h"
#include "game/Unit.h"
#include "game/Map.h"

#include "util/UtilString.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Perk ctor and dtor
///////////////////////////////////////////////////////////////////////////////

Perk::Perk(const std::string& name, Stats s, float dur, bool lua, int maxStacks)
	: _name(name), _attached(nullptr), _stats(s), _duration(dur),
		_maxDuration(dur), _stacks(1), _maxStacks(maxStacks), _stackable(false),
		_toRemove(false) {

	if (maxStacks > 0) {
		_stackable = true;
	}

	if (lua) {
		_script.loadScript("./lua/" + name + ".lua");
		loadLua();
	}
}

Perk::Perk(const Perk& perk)
	: _name(perk._name), _attached(perk._attached), _stats(perk._stats),
		_duration(perk._duration), _maxDuration(perk._maxDuration),
		_stacks(perk._stacks), _maxStacks(perk._maxStacks),
		_stackable(perk._stackable), _toRemove(perk._toRemove) {
	
}

Perk::~Perk() {
	_attached = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Perk::loadLua() {
	if (_script.isLoaded()) {
		AG_WARN("[Perk %x] Loading a loaded script [%x]", this, &_script);
	}

	_script.lua.set_function("getObjectsInRange",
			[this](float x, float y, float r) {
		return _attached->getMap()->getObjectsInRange(x, y, r);	
	});

	_script.lua.set("attached", _attached);
	_script.lua.set("me", this);
}

///////////////////////////////////////////////////////////////////////////////
// Updating methods
///////////////////////////////////////////////////////////////////////////////

void Perk::update(int diff) {
	if (_duration <= -1.0f) {
		return;
	}
	_duration -= (diff * 0.000001f);
	if (_duration <= 0.0f) {
		AG_INFO("[Perk %x] \'%s\' is done", this, getName().c_str());
		_toRemove = true;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Getters and Setters
///////////////////////////////////////////////////////////////////////////////

std::string Perk::getTitle() const {
	return (getName() + "(" + ag::String::toString(getStacks()) + "/" +
		ag::String::toString(getMaxStacks()) + ")");
}

void Perk::setStacks(int c) {
    if (c > _maxStacks || c < 0) {
        AG_INFO("Perk:: c: %i, _maxStacks: %i", c, _maxStacks);
        return;
    }
	// If not stackable reset the duration, else set the stacks
    if (!_stackable) {
        _duration = _maxDuration;
    } else {
        _stacks = c;
    }
}

void Perk::addStack() {
	// If stackable add a stack
	if (_stackable && (_stacks < _maxStacks)) {
		++_stacks;
	} else {
		// If not stackable, or at max stacks reset the duration
        _duration = _maxDuration;
    }
}

void Perk::setAttached(Unit* attached) {
	_attached = attached;
	// Make sure to update what Object we're attached to
	_script.lua.set("attached", _attached);
}
