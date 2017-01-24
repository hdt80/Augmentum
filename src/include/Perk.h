#ifndef _PERK_H
#define _PERK_H

#include <string>
#include "Stats.h"
#include "LuaScript.h"
#include "Scriptable.h"

class Object;
class Unit;

// A permentant stat change. When a Perk is added the base stats will be
// changed, and when removed the opposite of the Perk is removed.
class Perk : public Scriptable {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////

	// Ctor for Perk
	// name - Display name to use
	// s - Stats of thie Perk
	// dur - How many seconds the Perk will last
	// lua - If there is an attached lua script
	// maxStacks - How many stacks of the Perk there can be
	Perk(const std::string& name, Stats s, float dur, bool lua,
		int maxStacks = 0);

	// Copy ctor for Perk
	// perk - Perk to copy from
	Perk(const Perk& perk);

	// Perk dtor
	virtual ~Perk();

	// Methods /////////////////////////////////////////////////////////////////

	// Load the lua script used when events occur
	void loadLua();

	// Simulate the Perk for an amount of time
	// diff - Microseconds to simulate the Perk for
	void update(int diff);

	// Getters and setters /////////////////////////////////////////////////////
	
	// Set the Unit this Perk is attached to
	// attached - Unit this Perk is attached to
	void setAttached(Unit* attached);

	// Get the Object this Perk is attached to
	// returns: _attached
	inline Unit* getAttached() const { return _attached; }

	// Get how many more seconds this Perk is active for
	// returns: _duration
	inline float getDuration() const { return _duration; }

	// Set how much longer this Perk will last for
	// d - New duation of the Perk
	inline void setDuration(float d) { _duration = d; }

	// Get just how many seconds, no decimals this Perk is active for
    //		Add 0.5f so the value is always rounded up
	// returns: _duration plus 0.5 casted to an int
    inline int getShortDuration() const { return (int)(_duration + 0.5f); }

	// Get how long this Perk lasts for
	// returns: _maxDuration
	inline float getMaxDuration() const { return _maxDuration; }

	// Get just how many seconds, no decimals this Perks last for
	// returns: An int cast of _maxDuration
	inline int getShortMaxDuration() const { return (int)_maxDuration; }

	// Stack getters and setters ///////////////////////////////////////////////

	// Get how many stacks this Perk currently has
	// returns: _stacks
	inline int getStacks() const { return _stacks; }

	// Get the max amount of stacks this Perk can have
	// returns: _maxStacks
	inline int getMaxStacks() const { return _maxStacks; }

	// See if this Perk is stackable
	// returns: _stackable
	inline bool isStackable() const { return _stackable; }

	// Set if the Perk is stackable for not
	// b - Is the Perk stackable?
	inline void setStackable(bool b) { _stackable = b; }

	// Set how many stacks this Perk currently has
	// c - Stacks of the perk
    void setStacks(int c);

	// Add a single stack to the Perk
	void addStack();

	// Remove a single stack from the Perk
	void removeStack() { _stacks--; }

	// Other getters and setters ///////////////////////////////////////////////

	// Check if this Perk is queued for removal
	// returns: _toRemove
	inline bool isToRemove() const { return _toRemove; }

	// Get the display name of this Perk
	// returns: _name
	const std::string& getName() const { return _name; }

	// Get the name and how many stacks this Perk has. Used to display the Perk
	//		in a Gui component
	// returns: The name of this Perk and how many stacks it has
	std::string getTitle() const;

	// Get the Stats this Perk provides to the attached Unit
	// returns: A const reference to _stats
	inline const Stats& getStats() const { return _stats; }

	// Get the Stats this Perk provides to the attached Object
	// returns: A reference to _stats
	inline Stats& getStats() { return _stats; }

protected:
	std::string _name; // Display name of the perk

	// Scripts to be called when the Object calls each respective Method
	// _name is the path of the script under ./lua/$(_name).lua
	LuaScript _lua;

	Unit* _attached; // Object we're attached to

	Stats _stats; // Stats applied to the Object
	float _duration; // -1 duration means infinite
	float _maxDuration; //_duration changes each update, but _maxDuration doesnt

	int _stacks; // How many stacks of this Perk there currently are
	int _maxStacks; // How many stacks this Perk can have at any time

	// If statckable applying a new perk with the same name will add a stack
	// If not stackable and applying the same perk the _duration will be reset
	// to the new perks duration
	bool _stackable;

	bool _toRemove; // Marked for removal
};

#endif
