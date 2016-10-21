#ifndef _COOLDOWN_H
#define _COOLDOWN_H

class Cooldown {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Ctor for cooldown
	// defaultCD = Default cooldown to use. A value of -1 means no default set
	Cooldown(int maxCooldown = -1);
	~Cooldown();

	// Methods /////////////////////////////////////////////////////////////////

	// Simulate the Cooldown for an amount of microseconds
	// diff - Microseconds to simulate for
	void update(int diff);

	// Trigger the cooldown and set the _timeLeft to _defaultCooldown
	void start();

	// Get how close to be done this Cooldown is
	// 0: All the way done, no cooldown
	// 1: Cooldown just started, at max value
	// Can go higher if addTime adds more that _defaultCooldown
	// returns: _defaultCooldown / _timeLeft
	inline float getRatioDone() { return _maxCooldown / _timeLeft; }

	// Add microseconds to the Cooldown
	// microseconds - Microseconds to add. The cooldown does not have to be done
	void addTime(int microseconds);

	// Get how many microseconds left till the Cooldown is done
	// returns: _timeLeft
	inline float getTimeLeft() { return _timeLeft; }

	// Check if the Cooldown has completed
	// returns: If _timeLeft <= 0
	inline bool done() { return _timeLeft <= 0; }

	// Get the default cooldown
	// returns: _defaultCooldown
	inline int getMaxCooldown() { return _maxCooldown; }

	// Set the default cooldown
	// def - What to set _defaultCooldown to
	inline void setMaxCooldown(int def) { _maxCooldown = def; }

protected:
	int _timeLeft; // Microseconds till this Cooldown is over
	int _maxCooldown; // Default cooldown when trigger()ed
};

#endif