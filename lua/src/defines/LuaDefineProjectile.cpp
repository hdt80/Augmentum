#include "LuaDefines.h"

#include "game/Projectile.h"
#include "game/Target.h"
#include "game/Map.h"

namespace LuaDefines {
	void defineProjectile(sol::state& lua) {
		lua.new_usertype<Projectile>(
			"Projectile", sol::constructors<
				sol::types<Map*, int, Target*, Unit*, sf::Color>>(),
			"distanceWith", sol::overload(sol::resolve
				<float(float, float)>(&Projectile::distanceWith)),
			"distanceWithSqr", sol::overload(sol::resolve
				<float(float, float)>(&Projectile::distanceWithSqr)),
			"getX", &Projectile::getX,
			"getY", &Projectile::getY,
			"isSimpleTarget", &Projectile::isSimpleTarget,
			"getObjectType", &Projectile::getObjectType,
			"isObjectTypeOptionSet", &Projectile::isObjectTypeOptionSet,
			"setVelocity", &Projectile::setVelocity,
			"updatePosition", &Projectile::updatePosition,
			"setPosition", sol::overload(
				sol::resolve<void(float, float)>(&Projectile::setPosition)),
			"getSize", &Projectile::getSize,
			"hasCollision", &Projectile::hasCollision,
			"contains", &Projectile::contains,
			"collidesWith", &Projectile::collidesWith,
			"getMap", &Projectile::getMap,
			"isToRemove", &Projectile::isToRemove,
			"getVelocity", &Projectile::getVelocity,
			"getX", &Projectile::getX,
			"getY", &Projectile::getY,
			"dealDamage", &Projectile::dealDamage,
			"setHealth", &Projectile::setHealth,
			"getHealth", sol::overload(
				sol::resolve<float(void) const>(&Projectile::getHealth)),
			"setHealth", &Projectile::setHealth,
			"getMaxHealth", sol::overload(
				sol::resolve<float(void) const>(&Projectile::getMaxHealth)),
			"setMaxHealth", &Projectile::setMaxHealth,
			"isInvulerable", &Projectile::isInvulerable,
			"setInvulerable", &Projectile::setInvulerable,
			"canShoot", &Projectile::canShoot,
			"shoot", sol::overload(
				sol::resolve<void(float, float)>(&Projectile::shoot)),
			"getExpToNextLevel", &Projectile::getExpToNextLevel,
			"getExpForCurrentLevel", &Projectile::getExpForCurrentLevel,
			"getLevel", &Projectile::getLevel,
			"getExp", sol::overload(
				sol::resolve<float(void) const>(&Projectile::getExp)),
			"addExp", &Projectile::addExp,
			"setExp", &Projectile::setExp,
			"setLevel", &Projectile::setLevel,
			"applyStat", &Projectile::applyStat,
			"setStats", &Projectile::setStats,
			"getStatMod", &Projectile::getStatMod,
			"getStats", &Projectile::getStats,
			"getBaseStats", &Projectile::getBaseStats,
			"getStat", &Projectile::getStat,
			"setStat", &Projectile::setStat,
			"getPerks", &Projectile::getPerks,
			"addPerk", &Projectile::addPerk,
			"removePerk", &Projectile::removePerk,
			"hasPerk", &Projectile::hasPerk,
			"getPerk", &Projectile::getPerk,
			"setToRemove", &Projectile::setToRemove,
			"getShooter", &Projectile::getShooter
		);
	}
};
