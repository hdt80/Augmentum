#pragma once

#include "logger/Logger.h"

#include <sol/sol.hpp>

#include <map>
#include <string>

template<typename T>
class Database {
public:
	// Methods /////////////////////////////////////////////////////////////////
	
	// Store an object into the database. If the object is already in the
	//		database it will override the previous value
	//
	// name - Name to store the object as
	// obj - Object to store
	//
	void store(const std::string& name, T obj) {
		_database[name] = obj;
	}

	// Retrieve an object from the database
	//
	// name - Name of the object to retrieve
	//
	// returns: A reference to the matching T
	//
	const T& get(const std::string& name) const {
		if (!isStored(name)) {
			AG_WARN("[Database] Failed to find %s.", name.c_str());
			return _default;
		}
		return _database.at(name);
	}

	// Check if an object is loaded and stored in the Database
	//
	// name - Name to check for
	//
	// returns: If the name has a mapped value in the Database
	//
	inline bool isStored(const std::string& name) const {
		return _database.find(name) != _database.end();
	}

	// Check if an object is loaded and stored in the Database
	//
	// name - Name to check for
	//
	// returns: If the name has a mapped value in the Database
	//
	inline bool has(const std::string& name) const { return isStored(name); }

	// Get the default value to return if no obj under a name if found
	//
	// returns: Copy of the default value
	//
	inline const T& getDefault() const { return _default; }

	// Set the default value to return if no obj under a name if found
	//
	// def - Default value to return
	//
	inline void setDefault(const T& def) { _default = def; }

	// Load entries from a file. This file should be a Lua file. In order for
	//		the entires to load proprly they must be a derived class of 
	//		LuaConfigEntry. If a Database of a type called loadFromFile and its
	//		type is not a LuaConfigEntry it will not compile. Entries are read
	//		from the file at filePath, and iterated through the table with the
	//		name of tableName to load each entry. Each entry will have its own
	//		name, which will be the name the entry is saved under. Any
	//		duplicates will be overridden.
	//
	// filePath - Path to the file. This is relative to the currently working
	//		directory of the program. This should include the file extension.
	// tableName - Name of the table the values are loaded from. Any periods in
	//		the tableName indicate a sub-table of another table. The tableName
	//		can be any name, but generally the type of the entry being loaded
	//		is used for clarity.
	//
	void loadFromFile(const std::string& filePath,
		const std::string& tableName) {

		sol::state lua;
		lua.open_libraries(sol::lib::base, sol::lib::table, sol::lib::package);

		try {
			lua.require_file("Colors", "./lua/lib/Colors.lua");
		} catch (const sol::error& e) {
			AG_ERROR("Error when loading base file: %s", e.what());
		}

		try {
			lua.script_file(filePath);
		} catch (const sol::error& e) {
			AG_ERROR("Error loading %s: %s", filePath.c_str(), e.what());
			return;
		}

		sol::table table = lua[tableName];
		if (!table.valid()) {
			AG_ERROR("Invalid table of %s", tableName.c_str());
			return;
		}

		// Iterate thru the table and load all the valid entries
		auto iter = table.begin();
		while (iter != table.end()) {
			std::string key = (*iter).first.as<std::string>();
			sol::table val = (*iter).second.as<sol::table>();
			++iter;

			T entry;
			entry.readFromTable(val);

			store(key, entry);
		}
	}

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	std::map<std::string, T> _database; // Mapped stored objects
	 T _default; // Default value
};
