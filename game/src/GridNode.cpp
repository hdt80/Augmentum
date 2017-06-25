#include "game/GridNode.h"

#include "game/Unit.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GridNode::GridNode()
	: LuaConfigEntry("GridNode"), _internalName("DEFAULT"),
		_displayName("DEFAULT"), _tooltip("DEFAULT TOOLTIP"), _perk(nullptr),
		_unlocked(false), _attached(nullptr), _minLevel(0), _level(0),
		_maxLevel(0) {

}

GridNode::GridNode(const sol::table& table)
	: LuaConfigEntry("GridNode") {
	
	readFromTable(table);
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloads
////////////////////////////////////////////////////////////////////////////////

bool GridNode::operator==(const GridNode& node) const {
	return _internalName == node._internalName;
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void GridNode::finalize() {

}

void GridNode::readFromTable(const sol::table& table) {

}

bool GridNode::isUnlocked() const {
	return (parentsUnlocked()
		&& (getCurrentLevel() < getMaxLevel())
		&& (_attached->getLevel() >= getMinLevel()));
}

bool GridNode::isUnleveled() const {
	return (isUnlocked()
		&& (getCurrentLevel() == 0));
}

bool GridNode::isCompleted() const {
	return (parentsUnlocked()
		&& (getCurrentLevel() == getMaxLevel()));
}


bool GridNode::parentsUnlocked() const {
	for (const GridNode* node : _parents) {
		if (!node->isUnlocked() && node->getCurrentLevel() <= 0) {
			return false;
		}
	}
	return true;
}
