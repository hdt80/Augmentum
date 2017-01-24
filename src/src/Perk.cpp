#include "Perk.h"

#include "Logger.h"
#include "Object.h"
#include "Unit.h"
#include "Map.h"

#include "util/StringUtil.h"

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
		_lua.loadScript("./lua/" + name + ".lua");
		loadLua();
	}
}

Perk::Perk(const Perk& perk)
	: _name(perk._name), _attached(perk._attached), _stats(perk._stats),
		_duration(perk._duration), _maxDuration(perk._maxDuration), 
		_stacks(perk._stacks), _maxStacks(perk._maxStacks),
		_stackable(perk._stackable), _toRemove(perk._toRemove) {
	
}

Perk::~Perk() {}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Perk::loadLua() {
	if (_lua.isLoaded()) {
		CORE_WARNING("[Perk %x] Loading a loaded script [%x]", this, &_lua);
	}

	_lua.lua.set_function("getObjectsInRange",
			[this](float x, float y, float r) {
		return _attached->getMap()->getObjectsInRange(x, y, r);	
	});

	_lua.lua.set("attached", _attached);
	_lua.lua.set("me", this);
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
		CORE_INFO("[Perk %x] \'%s\' is done", this, getName().c_str());
		_toRemove = true;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Getters and Setters
///////////////////////////////////////////////////////////////////////////////

std::string Perk::getTitle() const {
	return (getName() + "(" + StringUtil::toString(getStacks()) + "/" +
		StringUtil::toString(getMaxStacks()) + ")");
}

void Perk::setStacks(int c) {
    if (c > _maxStacks || c < 0) {
        CORE_INFO("Perk:: c: %i, _maxStacks: %i", c, _maxStacks);
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
	_lua.lua.set("attached", _attached);
}
