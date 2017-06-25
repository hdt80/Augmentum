#include "game/Stats.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Stats ctor
////////////////////////////////////////////////////////////////////////////////

Stats::Stats(bool perc)
	: LuaConfigEntry("Stats"),
		percent(perc) {

	// Add default stats
	addStat("range", 500.0f);
	addStat("fireRate", 2.0f); // Attacks per second
	addStat("damage", 2.0f);
	addStat("speed", 20.0f);
	addStat("projSpeed", 50.0f);
	addStat("accel", 1.1f); // % increase
	addStat("maxHealth", 30.0f);
}

Stats::Stats(float def)
	: LuaConfigEntry("Stats"),
		percent(false) {

	addStat("range", def);
	addStat("fireRate", def); // Attacks per second
	addStat("damage", def);
	addStat("speed", def);
	addStat("projSpeed", def);
	addStat("accel", def); // % increase
	addStat("maxHealth", def);
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

void Stats::readFromTable(const sol::table& table) {
	// Iterator vars
	std::string key;
	float value;

	// Iterate through each value in the table
	auto iter = table.begin();
	AG_DEBUG("Stats iter:");
	while (iter != table.end()) {
		key = (*iter).first.as<std::string>();
		value = (*iter).second.as<float>();
		if (!hasStat(key)) {
			addStat(key, value);	
		} else {
			setStat(key, value);
		}
		AG_DEBUG("\t%s : %g", key.c_str(), value);

		++iter;
	}
}

void Stats::print() const {
	AG_INFO("[Stats %x]", this);
	for (auto i : stats) {
		AG_INFO("\t%s:%g", i.first.c_str(), i.second);
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
		AG_WARN("[Stats %x] \'%s\' isn't in this stats", this, name.c_str());
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
		AG_WARN("[Stats %x] Already contains \'%s\': %g",
			this, name.c_str(), getStat(name));
	}
	stats.insert({name, value});
}

void Stats::setStat(const std::string& name, float value) {
	stats.at(name) = value;
}
