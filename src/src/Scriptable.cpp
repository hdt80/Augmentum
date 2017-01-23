#include "Scriptable.h"

#include "Object.h"
#include "Entity.h"
#include "Unit.h"
#include "Projectile.h"

////////////////////////////////////////////////////////////////////////////////
// Scriptable ctor and dtor
////////////////////////////////////////////////////////////////////////////////

Scriptable::~Scriptable() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

bool Scriptable::loadFile(const std::string& filepath) {
	_script.loadScript(filepath);
	return _script.isLoaded();
}

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////

void Scriptable::onUpdate(int diff) {
	_script.callFunction("onUpdate", diff);
}

void Scriptable::onApply(Unit* unit) {
	_script.callFunction("onApply", unit);
}

void Scriptable::onCollision(Object* o) {
	_script.callFunction("onCollision", o);
}

void Scriptable::onProjectileHit(Projectile* p) {
	_script.callFunction("onProjectileHit", p);
}

void Scriptable::onShoot(float x, float y) {
	_script.callFunction("onShoot", x, y);
}

void Scriptable::onMove(int diff) {
	_script.callFunction("onMove", diff);
}

void Scriptable::onDamageDealt(int dmg, Entity* hit) {
	_script.callFunction("onDamageDealt", dmg, hit);
}

void Scriptable::onDamageTaken(int dmg, Unit* attacker) {
	_script.callFunction("onDamageTaken", dmg, attacker);
}

void Scriptable::onDeath() {
	_script.callFunction("onDeath");
}

void Scriptable::onKilled(Unit* killer) {
	_script.callFunction("onKilled", killer);
}

void Scriptable::onLevelUp(int newLevel) {
	_script.callFunction("onLevelUp", newLevel);
}

void Scriptable::onEntityKilled(Entity* killed) {
	_script.callFunction("onUnitKilled", killed);
}
