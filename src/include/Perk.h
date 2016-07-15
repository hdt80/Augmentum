#ifndef _PERK_H
#define _PERK_H

#include <string>
#include "Stats.h"
#include "LuaScript.h"

class Object;

// A permentant stat change. When a Perk is added the base stats will be
// changed, and when removed the opposite of the Perk is removed.
class Perk {
public:
	// More than one max stack means a perk is stackable
	Perk(std::string name, Stats s, float dur, bool lua, int maxStacks = 0);
	~Perk();

	void loadLua();

	Perk* clone();

	void update(int diff);

	// Each event is called when the attached Object calls it
	void onUpdate(int diff);
	void onMove(int diff);
	void onShoot(Object* target);
	void onDamageDealt(int dmg, Object* hit);
	void onDamageTaken(int dmg, Object* hitter);
	void onDeath();
    void onApply(Object* attached);

	void setAttached(Object* attached);
	Object* getAttached() { return _attached; }

	std::string getName() const { return _name; }
	std::string getTitle() const;
	Stats* getStats() { return &_stats; }
	float getDuration() const { return _duration; }
    // Add 0.5f so the value is always rounded up
    int getShortDuration() const { return (int)(_duration + 0.5f); }
	float getMaxDuration() const { return _maxDuration; }
	int getShortMaxDuration() const { return (int)_maxDuration; }
	int getStacks() const { return _stacks; }
	int getMaxStacks() const { return _maxStacks; }
	bool isStackable() const { return _stackable; }
	bool isToRemove() const { return _toRemove; }

	void setDuration(float d) { _duration = d; }
	void setStackable(bool b) { _stackable = b; }
    void setStacks(int c);
	void addStack();
	void removeStack() { _stacks--; }

protected:
	std::string _name; // Display name of the perk

	// Scripts to be called when the Object calls each respective Method
	// _name is the path of the script under ./lua/$(_name).lua
	LuaScript _lua;
	Object* _attached; // Object we're attached to

	Stats _stats; // Stats applied to the Object
	float _duration; // -1 duration means infinite
	float _maxDuration; //_duration changes each update, but _maxDuration doesnt

	int _stacks;
	int _maxStacks;
	// If statckable applying a new perk with the same name will add a stack
	// If not stackable and applying the same perk the _duration will be reset
	// to the new perks duration
	bool _stackable;

	bool _toRemove; // Marked for removal
};

#endif
