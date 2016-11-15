#ifndef _STATS_H
#define _STATS_H

#include <string>
#include <map>
#include "LuaConfigEntry.h"

class Stats : public LuaConfigEntry {
public:
	// Stats ctor //////////////////////////////////////////////////////////////
	
	// Stats ctor
	// perc - If the Stats signify a percentage diff
	Stats(bool perc = false);

	// Stats ctor
	// def - Default value to set the default stats to
	Stats(float def);

	// Operator overloads //////////////////////////////////////////////////////

	// Negative operator
	Stats operator- () const;

	// Add two stats up by iterating thru each stat in each Stat
	// s - Stats to add to this Stats
	// returns: A stats that has the sum of each Stat
	Stats operator+ (const Stats& s) const;

	// Add a Stats to another stat
	// s - Stats to add
	void operator+=(const Stats& s);

	// Multiple each stat in the Stats by a constant
	// m - Multipler to multiple each stat by
	// returns: A Stats that has each stat multiplied by m
    Stats operator* (float m) const;

	// Setter for a stat
	// s - Stat to change
	// returns: A reference to the stat that matches s
	float& operator[](const std::string& s);

	// Getter for a stat
	// s - Stat to get
	// returns: The value of the stat that matches s
	float operator[](const std::string& s) const;

	// Methods /////////////////////////////////////////////////////////////////
	
	// Inheritred from LuaConfigEntry
	virtual void readFromTable(const sol::table& table);

	// Print all the value in this Stats
	void print() const;

	// Add a new stat
	// name - Name to use to store the stat
	// value - Value to set the stat to
	void addStat(const std::string& name, float value);

	// Set a new stat
	// name - Name of the stat to set
	// value - New value to set the matching stat to
	void setStat(const std::string& name, float value);

	// Check if this Stats has a stat
	// name - Name of the stat to check for
	// returns: If this Stats has the name
	bool hasStat(const std::string& name) const;

	// Get the value of a stat
	// name - Name of the stat to get
	// returns: Value of the stat, or 0 if that stat is not stored in this Stats
	float getStat(const std::string& name) const;

    //A percentage Stat is used by Perks. Percent stats take base stats
    //To calculate new values.
    //Eg. range(500) * range(0.5) = 250
    //With a base stat of 500 range a 0.5 (50%) increase will add 250 range
    //to make 500 range
    bool percent;

protected:
	std::map<std::string, float> stats; // Stats
};

#endif
