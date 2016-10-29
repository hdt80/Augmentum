#include "Stats.h"

#include "Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Stats ctor
////////////////////////////////////////////////////////////////////////////////

Stats::Stats(bool perc) : percent(perc)  {
	// Add default stats
	addStat("range", 0.0f);
	addStat("fireRate", 0.0f);
	addStat("damage", 0.0f);
	addStat("speed", 1.0f);
	addStat("projSpeed", 0.0f);
	addStat("accel", 0.0f);
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloads
////////////////////////////////////////////////////////////////////////////////

Stats Stats::operator- () const {
	Stats s;
	for (auto i : stats) {
		s.addStat(i.first, -1 * i.second);
	}
	return s;
}

Stats Stats::operator* (float m) const {
    Stats s;
	for (auto i : stats) {
		s.addStat(i.first, i.second * m);
	}
	return s;
}

Stats Stats::operator+ (const Stats& o) const {
	Stats s;
	for (auto i : stats) {
		if (o.hasStat(i.first)) {
			s.setStat(i.first, (getStat(i.first) + o.getStat(i.first)));
		} else {
			s.addStat(i.first, (getStat(i.first) + o.getStat(i.first)));
		}
	}
	return s;
}

void Stats::operator+= (const Stats& o) {
	*this = *this + o;
}

float Stats::operator[](const std::string& s) const {
	if (hasStat(s)) {
		return getStat(s);
	}
	return 0.0f;
}

float& Stats::operator[](const std::string& s) {
	return stats[s];
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Stats::print() const {
	CORE_INFO("[Stats %x]", this);
	for (auto i : stats) {
		CORE_INFO("\t%s:%g", i.first.c_str(), i.second);
	}
}

////////////////////////////////////////////////////////////////////////////////
// Getter and setters
////////////////////////////////////////////////////////////////////////////////

bool Stats::hasStat(const std::string& name) const {
	return (stats.find(name) != stats.end());
}

float Stats::getStat(const std::string& name) const {
	if (!hasStat(name)) {
		CORE_WARN("[Stats %x] \'%s\' isn't in this stats", this, name.c_str());
		return 0;
	}
	try {
		return stats.at(name);
	} catch (std::out_of_range e) {
		return 0;
	}
}

void Stats::addStat(const std::string& name, float value) {
	if (hasStat(name)) {
		CORE_WARN("[Stats %x] Already contains \'%s\': %g",
			this, name.c_str(), getStat(name));
	}
	stats.insert({name, value});
}

void Stats::setStat(const std::string& name, float value) {
	stats.at(name) = value;
}
