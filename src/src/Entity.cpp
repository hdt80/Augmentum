#include "Entity.h"

////////////////////////////////////////////////////////////////////////////////
// Entity ctor and dtor
////////////////////////////////////////////////////////////////////////////////

Entity::Entity(Map* map, float x, float y, int size, int maxHealth)
	: Object(map, x, y, size),
		_hpBar(Vector2(50.0f, 8.0f), sf::Color::Red, sf::Color::Green,
			0, _maxHealth, _health),
		_health(maxHealth), _maxHealth(maxHealth), _invulerable(false) {

	
}

Entity::~Entity() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Entity::dealDamage(float amount, Unit* source) {
	setHealth(getHealth() - amount);

	if (getHealth() <= 0) {
		setToRemove(true);
		onDeath();
	}
}

void Entity::updatePositon(float x, float y) {
	Object::updatePosition(x, y);
	_hpBar.setPosition(x - getSize(), y - getSize());
}

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////

void Entity::onProjectileHit(Projectile* p) {
	_lua.callFunction("onProjectileHit", p);
}

void Entity::onDamageTaken(int dmg, Unit* attacker) {

}

void Entity::onDeath() {

}

////////////////////////////////////////////////////////////////////////////////
// Health methods
////////////////////////////////////////////////////////////////////////////////

void Entity::setHealth(float health) {
	_health = health;
	if (_health > _maxHealth) {
		_health = getMaxHealth();
	}
}

void Entity::setMaxHealth(float health) {
	_maxHealth = health;
	if (_health > _maxHealth) {
		_health = getMaxHealth();
	}
}
