#ifndef _DATABASE_H
#define _DATABASE_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "GuiComponent.h"
#include "GuiProgressBar.h"

// Macro to define mangled class names during compilation
// To get the demangled name call TemplateTypeNames<T>; where T is the class
template<typename T>
struct TemplateTypeNames;

#define REGISTER_DEMANGLED_TYPE(X) template <> struct TemplateTypeNames<X> \
	{ static const char* name; } ; const char* TemplateTypeNames<X>::name = #X

template<typename T>
class Database {
public:
	// Store an object into the database
	// name - Name to store the object as
	// obj - Object to store
	void store(const std::string& name, T obj);

	// Retrieve an object from the database
	// name - Name of the object to retrieve
	// returns: T - A copy of the object that was found
	const T* get(const std::string& name);

	// Check if an object is loaded
	// name - Name to check for
	bool isStored(const std::string& name);

	// Get the default value to return if no obj under a name if found
	// returns: Copy of the default value
	T* getDefault() { return &_default; }

	// Set the default value to return if no obj under a name if found
	// def - Default value to return
	void setDefault(T def) { _default = def; }

protected:
	std::map<std::string, T> _database;
	 T _default;
};

namespace Databases {
	extern Database<sf::Font> FontDatabase;
	extern Database<GuiEntryStyle> GuiEntryStyleDatabase;
	extern Database<GuiComponentStyle> GuiComponentStyleDatabase;
	extern Database<GuiProgressBarStyle> GuiProgressBarStyleDatabase;
}

#endif
