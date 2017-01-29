#ifndef _DATABASE_H
#define _DATABASE_H

#include <map>
#include <string>

template<typename T>
struct TemplateTypeNames;

#define REGISTER_DEMANGLED_TYPE(X) template <> struct TemplateTypeNames<X> \
	{ static const char* name; } ; const char* TemplateTypeNames<X>::name = #X

// Types being put into a Database
#include <SFML/Graphics.hpp>
#include "gui_style/GuiEntryStyle.h"
#include "gui_style/GuiComponentStyle.h"
#include "gui_style/GuiProgressBarStyle.h"
#include "ParticleEmitter.h"

template<typename T>
class Database {
public:
	// Store an object into the database
	// name - Name to store the object as
	// obj - Object to store
	void store(const std::string& name, T obj);

	// Retrieve an object from the database
	// name - Name of the object to retrieve
	// returns: A reference to the matching T
	const T& get(const std::string& name) const;

	// Check if an object is loaded
	// name - Name to check for
	bool isStored(const std::string& name) const;

	// Get the default value to return if no obj under a name if found
	// returns: Copy of the default value
	inline const T& getDefault() const { return _default; }

	// Set the default value to return if no obj under a name if found
	// def - Default value to return
	void setDefault(const T& def) { _default = def; }

protected:
	std::map<std::string, T> _database; // Mapped stored objects
	 T _default; // Default value
};

// Database types that are allowed
namespace Databases {
	extern Database<sf::Font> FontDatabase;
	extern Database<GuiEntryStyle> GuiEntryStyleDatabase;
	extern Database<GuiComponentStyle> GuiComponentStyleDatabase;
	extern Database<GuiProgressBarStyle> GuiProgressBarStyleDatabase;
	extern Database<ParticleDef> ParticleDefDatabase;
}

#endif
