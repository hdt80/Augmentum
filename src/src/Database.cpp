#include "Database.h"

#include "ParticleEmitter.h"
#include "Logger.h"

#include <SFML/Graphics.hpp>
#include <typeinfo>

REGISTER_DEMANGLED_TYPE(sf::Font);
REGISTER_DEMANGLED_TYPE(GuiEntryStyle);
REGISTER_DEMANGLED_TYPE(GuiComponentStyle);
REGISTER_DEMANGLED_TYPE(GuiProgressBarStyle);
REGISTER_DEMANGLED_TYPE(ParticleDef);

template<typename T>
void Database<T>::store(const std::string& name, T obj) {
	if (isStored(name)) {
		CORE_WARN("[Database %s] Already has \'%s\'",
			TemplateTypeNames<T>::name, name.c_str());
		return;
	}
	_database[name] = obj;
}

template<typename T>
const T& Database<T>::get(const std::string& name) const {
	if (!isStored(name)) {
		CORE_WARN("[Database %s] Couldn't find \'%s\'. Returning default.",
			TemplateTypeNames<T>::name, name.c_str());
		return _default;
	}
	return _database.at(name);
}

template<typename T>
bool Database<T>::isStored(const std::string& name) const {
	typename std::map<std::string, T>::const_iterator it = _database.find(name);

	return it != _database.end();
}


////////////////////////////////////////////////////////////////////////////////
// Explicit instantations
////////////////////////////////////////////////////////////////////////////////

// Only allow these types of Databases
template class Database<sf::Font>;
template class Database<GuiEntryStyle>;
template class Database<GuiComponentStyle>;
template class Database<GuiProgressBarStyle>;
template class Database<ParticleDef>;

// Define all the databases used. Only these Databased can be created
namespace Databases {
	Database<sf::Font> FontDatabase;
	Database<GuiEntryStyle> GuiEntryStyleDatabase;
	Database<GuiComponentStyle> GuiComponentStyleDatabase;
	Database<GuiProgressBarStyle> GuiProgressBarStyleDatabase;
	Database<ParticleDef> ParticleDefDatabase;
}
