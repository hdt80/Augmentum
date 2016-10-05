#include "ExperienceHelper.h"
#include "Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void ExperienceHelper::populateList() {
	// TODO: Better level formula
	for (int i = 0; i < _maxLevel + 1; ++i) {
		_levelReqs[i] = i;
	}
	_maxValue = _levelReqs[_maxLevel - 1];
}

int ExperienceHelper::expToLevel(float exp) {
	// If they've hit max level no need to check
	if (exp >= _maxValue) {
		return _maxLevel;
	}

	// Find the lowest level 1st
	for (int i = 0; i < _maxLevel; ++i) {
		// If the exp needed to reach that level is too high we've reached
		// the min exp of the previous level
		if (_levelReqs[i] >= exp) {
			return i - 1;
		}
	}
	CORE_WARN("[ExpHelper] Exp %g isn't in levelReqs", exp);
	return 0;
}

float ExperienceHelper::levelToExp(int level) {
	if (level > _maxLevel) {
		return _maxLevel;
	}
	return _levelReqs[level];
}

float ExperienceHelper::getRemainingExp(float exp) {
	if (exp > _maxValue) {
		return 0; // Can't go any higher
	}
	return levelToExp(expToLevel(exp) + 1) - exp;
}

////////////////////////////////////////////////////////////////////////////////
// Static vars
////////////////////////////////////////////////////////////////////////////////

const int ExperienceHelper::_maxLevel;
float ExperienceHelper::_levelReqs[_maxLevel];
float ExperienceHelper::_maxValue;
