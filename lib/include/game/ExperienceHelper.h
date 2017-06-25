#pragma once

class ExperienceHelper {
public:	
	// Create the list of the min exp reqs for each level
	static void populateList();

	// Get the level that amount of exp means
	// exp - Amount of experience
	// returns: The level that much exp means
	static int expToLevel(float exp);

	// Get the min amount of experience needed to reach that level
	// level - Level to calculate
	// returns: The min exp needed to reach that level
	static float levelToExp(int level);

	// Get how much exp is needed to hit the next level
	// exp - Current exp amount
	// returns: How much exp is needed to reach the next level
	static float getRemainingExp(float exp);

protected:
	static const int _maxLevel = 99; // Max level
	static float _levelReqs[_maxLevel]; // Min exp to reach each level
	static float _maxValue; // Max exp that means the max level
};
