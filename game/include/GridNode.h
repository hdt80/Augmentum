#pragma once

#include "lua/LuaConfigEntry.h"

class Perk;
class Unit;

class GridNode : public LuaConfigEntry {
public:
	// Enum state //////////////////////////////////////////////////////////////
	enum GridNodeState {

		// An unleveled GridNode means the GridNode is now level 0, and will
		// level up once the attached Unit has leveled up. In this state the
		// GridNode provides no Perks, and any child GridNodes cannot be
		// unlocked
		unleveled,
		// An unlocked GridNode means the GridNode is now level 1 or higher, but
		// has not hit the max level yet, and will continue to level up when the
		// attached Unit does. Any GridNode that has the GridNode as a parent
		// GridNode can now be started/put into the unleveled state
		unlocked,
		// A completed GridNode means the GridNode has hit the max level the
		// GridNode can hit. It will provide all the Perks, but will no longer
		// level up when the attached Unit does
		completed
	};

	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Nullary ctor for a GridNode. This is used for the default value in
	//		Databases
	//
	GridNode();

	// GridNode ctor
	//
	// table - Table to load all the values from. The table can have the
	//		follwing values. If any value is not specified the default value
	//		is loaded.
	//
	//		name: string - Internal name to refer to the GridNode by
	//		displayName: string - Name to display in the SkillGrid
	//		tooltip: string - Tooltip for the GridNode
	//		x: int - X coord of the position of the GridNode
	//		y: int - Y coord of the position of the GridNode
	//		parents: string table - Name of GridNodes that must be unlocked
	//			before this GridNode can be started
	//		perk: string - Internal name of the Perk the GridNode will use
	//		minLevel: int - Min level to unlock the GridNode
	//		maxLevel: int - Max level the GridNode can be
	//
	GridNode(const sol::table& table);

	// GridNode dtor
	//
	virtual ~GridNode() {}

	// Operator overloads //////////////////////////////////////////////////////
	
	// Operator overload for ==
	//
	// node - GridNode to be compared to
	//
	// returns: If the GridNode is equal to node. GridNodes are equal when the
	//		_internalName is the same, as each _internalName must be unique
	//
	bool operator==(const GridNode& node) const;

	// Methods /////////////////////////////////////////////////////////////////
	
	// Load all the value from a sol::table, the table should have the same
	//		name as _name
	//
	// table - Table to load the values from
	//
	virtual void readFromTable(const sol::table& table);

	// Finalize the GridNode, finding all the GridNode parent pointers from the
	//		GridNodeDatabase
	//
	void finalize();

	// State getters ///////////////////////////////////////////////////////////
	
	// Check if the GridNode is unlocked. A GridNode is considered unlocked
	//		if the following conditions are met:
	//			All parent GridNodes are unlocked and have at least one level
	//			The GridNode has not reached max level
	//			The attached Unit meets the minimum level
	//		An unlocked GridNode means the GridNode can be leveled up, which
	//			includes level 0
	//
	// returns: If the GridNode is unlocked
	//
	bool isUnlocked() const;

	// Check if a GridNode is unleveled. A GridNode is considered unlocked if
	//		the following conditions are met:
	//			All the checks for isUnlocked() are passed
	//			The GridNode has a current level of 0
	//		An unleveled GridNode means the GridNode is at level 0, and is not
	//			providing any Perks to the attached Unit
	//
	// returns: If the GridNode is unleveled
	//
	bool isUnleveled() const;

	// Check if a GridNode is completed. A GridNode is considered unlocked if
	//		the following conditions are met:
	//			All parent GridNodes are unlocked and have at least one level
	//			The current level is equal to the max level
	//		A completed GridNode no longer levels up when the attached Unit does
	//
	// returns: If the GridNode is completed
	//
	bool isCompleted() const;

	// Setters /////////////////////////////////////////////////////////////////
	
	// Set the Unit the GridNode is attached to
	//
	// u - Unit the GridNde is now attached to
	//
	inline void setAttached(Unit* u) { _attached = u; }

	// Getters /////////////////////////////////////////////////////////////////
	
	// Get the Unit the GridNode is attached to
	//
	// returns: _attached
	//
	inline const Unit* getAttached() const { return _attached; }

	// Get the internal name of the GridNode
	//
	// returns: _name
	//
	inline const std::string& getInternalName() const { return _internalName; }

	// Get the display name of the GridNode
	//
	// returns: _displayName
	//
	inline const std::string& getDisplayName() const { return _displayName; }

	// Get the tooltip of the GridNode
	//
	// returns: _tooltip
	//
	inline const std::string& getTooltip() const { return _tooltip; }

	// Get the X coord of the position of the GridNode
	//
	// returns: _x
	//
	inline int getX() const { return _x; }

	// Get the Y coord of the position of the GridNode
	//
	// returns: _y
	//
	inline int getY() const { return _y; }

	// Get the Perk of the GridNode
	//
	// returns: _perk
	//
	inline const Perk* getPerk() const { return _perk; }

	// Get the parent GridNodes of the GridNode
	//
	// returns: _parents
	//
	inline const std::vector<GridNode*>& getParents() const { return _parents; }

	// Get the min level of the GridNode
	//
	// returns: _minLevel
	//
	inline int getMinLevel() const { return _minLevel; }

	// Get the current level of the GridNode
	//
	// returns: _level
	//
	inline int getCurrentLevel() const { return _level; }

	// Get the max level of the GridNode
	//
	// returns: _maxLevel
	//
	inline int getMaxLevel() const { return _maxLevel; }

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	// Internal name to refer to the GridNode by. This must be unique for each
	// GridNode loaded. Once an _internalName is stored any other GridNode that
	// have the same _internalName will not be loaded
	std::string _internalName;

	// Name that will be displayed on the SkillGrid. This does not have to be
	// unique for each GridNodes loaded
	std::string _displayName;

	// Tooltip to display on the SkillGrid. Newlines are determined during
	// runtime by the SkillGrid, split by words. In order to not seperate two
	// words, add an _ between the two instead of a space
	std::string _tooltip;

	// Perk the attached Unit will get. Because all Perks are loaded before
	// GridNodes are, we don't need to create a temporary std::string to use for
	// lookup later
	Perk* _perk;

	// Prerequist GridNodes that need to be unlocked before the GridNode can
	// be unlocked. This vector will be unpopulated until finalize() is called,
	// and the GridNode pointers are found
	std::vector<GridNode*> _parents;

	// This is used when loading all the GridNodes from lua files. Since the
	// GridNodes have no order they are loaded in, a pointer to them cannot be
	// stored in _parents. Once all the GridNodes have been loaded all of them
	// will have finalize() called on them, and a lookup for each GridNode
	// pointer from the GridNodeDatabase
	std::vector<std::string> _parentNames;

	// If the GridNode can still be leveled up (the current level has not hit
	// the max level), the GridNode is considered unlocked
	bool _unlocked;

	// Unit the GridNode is attached to and is providing Perks too
	Unit* _attached;

	// Position of the GridNode in the SkillGrid. This is 0 indexed, so if the
	// GridNode is at (0,0), this will be the top left corner of the SkillGrid.
	// Duplicate positions in the same SkillGrid cannot happen, and after the
	// first GridNode is loaded into a SkillGrid any other GridNode that shares
	// a position with a GridNode already inserted is ignored
	int _x, _y;

	// The SkillGrid used in Augmentum doesn't have points per GridNode, or
	// points that can be assigned, but rather ties into the leveling system
	// of Units. GridNodes have a minimum level needed to first be unlocked,
	// and once unlocked they will start at 0, and will not provide any Perks.
	// Once the attached Unit levels up with the GridNode at level 0, it will
	// hit level up, and start providing the associated Perks. Each time the
	// attached Unit levels up after the initial level up will level the
	// GridNode as well, until the max level is reached, at which point the
	// GridNode is considered maxed out

	// Level needed to first be eligible for starting/put to level 0. Once the
	// attached Unit has hit this level the attached Unit can start leveling
	// the GridNode
	int _minLevel;

	// Current level of the GridNode. This will start at 0 when the GridNode is
	// first unlocked. At level 0 no Perks will be provided to the attached
	// Unit. Once the attached Unit levels up while the GridNode is unlocked
	// then it will level up as well, becoming level 1, and will level up each
	// subsequent time the attached Unit levels up. Once this _level is equal
	// to the max level, this will stop leveling up
	int _level;

	// Max level the GridNode can have. Once the current level is equal to the
	// max level the GridNode will no longer level up with the attached Unit
	int _maxLevel;

	// Methods /////////////////////////////////////////////////////////////////
	
	// Check if the parents are unlocked. This is used in isUnlocked() and
	//		isCompleted()
	//
	// returns: If all parents are unlocked
	//
	bool parentsUnlocked() const;
};
