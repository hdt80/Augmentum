#include "lua/LuaDefines.h"

#include "game/Enemy.h"
#include "game/Map.h"

namespace LuaDefines {
	void defineEnemy(sol::state& lua) {
		lua.new_usertype<Enemy> (
			"Enemy", sol::constructors<
				sol::types<Map*, float, float, int, EnemyType>>(),
			"distanceWith", sol::overload(sol::resolve
				<float(float, float)>(&Enemy::distanceWith)),
			"distanceWithSqr", sol::overload(sol::resolve
				<float(float, float)>(&Enemy::distanceWithSqr)),
			"getX", &Enemy::getX,
			"getY", &Enemy::getY,
			"isSimpleTarget", &Enemy::isSimpleTarget,
			"getObjectType", &Enemy::getObjectType,
			"isObjectTypeOptionSet", &Enemy::isObjectTypeOptionSet,
			"setVelocity", &Enemy::setVelocity,
			"updatePosition", &Enemy::updatePosition,
			"setPosition", sol::overload(
				sol::resolve<void(float, float)>(&Enemy::setPosition)),
			"getSize", &Enemy::getSize,
			"hasCollision", &Enemy::hasCollision,
			"contains", &Enemy::contains,
			"collidesWith", &Enemy::collidesWith,
			"getMap", &Enemy::getMap,
			"isToRemove", &Enemy::isToRemove,
			"getVelocity", &Enemy::getVelocity,
			"getX", &Enemy::getX,
			"getY", &Enemy::getY,
			"dealDamage", &Enemy::dealDamage,
			"setHealth", &Enemy::setHealth,
			"getHealth", sol::overload(
				sol::resolve<float(void) const>(&Enemy::getHealth)),
			"setHealth", &Enemy::setHealth,
			"getMaxHealth", sol::overload(
				sol::resolve<float(void) const>(&Enemy::getMaxHealth)),
			"setMaxHealth", &Enemy::setMaxHealth,
			"isInvulerable", &Enemy::isInvulerable,
			"setInvulerable", &Enemy::setInvulerable,
			"canShoot", &Enemy::canShoot,
			"shoot", sol::overload(
				sol::resolve<void(float, float)>(&Enemy::shoot)),
			"getExpToNextLevel", &Enemy::getExpToNextLevel,
			"getExpForCurrentLevel", &Enemy::getExpForCurrentLevel,
			"getLevel", &Enemy::getLevel,
			"getExp", sol::overload(
				sol::resolve<float(void) const>(&Enemy::getExp)),
			"addExp", &Enemy::addExp,
			"setExp", &Enemy::setExp,
			"setLevel", &Enemy::setLevel,
			"applyStat", &Enemy::applyStat,
			"setStats", &Enemy::setStats,
			"getStatMod", &Enemy::getStatMod,
			"getStats", &Enemy::getStats,
			"getBaseStats", &Enemy::getBaseStats,
			"getStat", &Enemy::getStat,
			"setStat", &Enemy::setStat,
			"getPerks", &Enemy::getPerks,
			"addPerk", &Enemy::addPerk,
			"removePerk", &Enemy::removePerk,
			"hasPerk", &Enemy::hasPerk,
			"getPerk", &Enemy::getPerk,
			"getEnemyType", &Enemy::getEnemyType,
			"setToRemove", &Enemy::setToRemove
		);
	}
};
