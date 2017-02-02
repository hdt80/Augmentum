#ifndef _DATABASE_H
#define _DATABASE_H

#include "Logger.h"

#include <map>
#include <string>

template<typename T>
class Database {
public:
	// Methods /////////////////////////////////////////////////////////////////
	
	// Store an object into the database. If the object is already in the
	//		database it will override the previous value
	// name - Name to store the object as
	// obj - Object to store
	void store(const std::string& name, T obj) {
		_database[name] = obj;
	}

	// Retrieve an object from the database
	// name - Name of the object to retrieve
	// returns: A reference to the matching T
	const T& get(const std::string& name) const {
		if (!isStored(name)) {
			CORE_WARN("[Database] Failed to find %s.", name.c_str());
			return _default;
		}
		return _database.at(name);
	}

	// Check if an object is loaded and stored in the Database
	// name - Name to check for
	// returns: If the name has a mapped value in the Database
	bool isStored(const std::string& name) const {
		return _database.find(name) != _database.end();
	}

	// Get the default value to return if no obj under a name if found
	// returns: Copy of the default value
	inline const T& getDefault() const { return _default; }

	// Set the default value to return if no obj under a name if found
	// def - Default value to return
	void setDefault(const T& def) { _default = def; }

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	std::map<std::string, T> _database; // Mapped stored objects
	 T _default; // Default value
};

#endif
