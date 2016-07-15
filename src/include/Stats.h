#ifndef _STATS_H
#define _STATS_H

#include <string>
#include <map>

class Stats {
public:
	Stats(bool perc = false);

	// Negative operator
	Stats operator- () const;

	Stats operator+ (const Stats& s) const;
	void operator+=(const Stats& s);
    Stats operator* (float m) const;

	// Bracket operators to get specific stats
	float& operator[](std::string s);
	float operator[](std::string s) const;

	void print() const;

	void addStat(std::string name, float value);
	void setStat(std::string name, float value);
	bool hasStat(std::string name) const;
	float getStat(std::string name) const;

    //A percentage Stat is used by Perks. Percent stats take base stats
    //To calculate new values.
    //Eg. range(500) * range(0.5) = 250
    //With a base stat of 500 range a 0.5 (50%) increase will add 250 range
    //to make 500 range
    bool percent;

protected:
	std::map<std::string, float> stats;

};

#endif
