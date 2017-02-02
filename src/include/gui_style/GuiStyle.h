#ifndef _GUI_STYLE_H
#define _GUI_STYLE_H

#include "LuaConfigEntry.h"

#include <SFML/Graphics.hpp>

#include "Logger.h"
#include "Database.h"

class GuiStyle : public LuaConfigEntry {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// GuiStyle ctor
	// name - Name of the LuaConfigEntry that the values will be loaded from
	GuiStyle(const std::string& name);

	// Static methods //////////////////////////////////////////////////////////
	
	// Load all the data from a specific file. The file will have a root table
	//		with the name of the type that is being loaded (typeName). Each 
	//		sub-table within this root table will have a name, which is the name
	//		that the loaded data will be stored. The data will be loaded from
	//		the sub-table into the new LuaConfigEntry. The LuaConfigEntry must
	//		have the method readFromTable defined for this method to function
	//		properly
	// filePath - Path to the file to load the data from. The path is relative
	//		to the current working directory of the program. Ths path will
	//		include the file extension as well as the name. No extension will
	//		be assumed
	// typeName - Name the look for the root table. This is typicaly the same as
	//		the templated type T.
	// database - Database to store the loaded data into. The key used to store
	//		the loaded data will be the name of the sub-table the data is loaded
	//		from
	// template T - Type of data that is being loaded. This must be derived
	//		from LuaConfigEntry, or else any type will cause a compiliation
	//		error
	template<typename T>
	static void loadFromFile(const std::string& filePath,
			const std::string& typeName, Database<T>& database) {
		sol::state lua;

		try {
			lua.script_file(filePath);
		} catch (const sol::error& e) {
			CORE_ERROR("Failed to find file %s", filePath.c_str());
			return;
		}

		sol::table table = lua[typeName];
		if (!table.valid()) {
			return;
		}

		auto iter = table.begin();
		while (iter != table.end()) {
			std::string key = (*iter).first.as<std::string>();
			sol::table val = (*iter).second.as<sol::table>();

			++iter;

			T style;
			style.readFromTable(val);

			database.template store(key, style);

			CORE_INFO("Stored %s", key.c_str());
		}
	}

	// Methods /////////////////////////////////////////////////////////////////
	
	// Load all the value from a sol::table, the table should have the same
	//		name as _name
	// table - Table to load the values from
	virtual void readFromTable(const sol::table& table) = 0;

protected:
	// Methods /////////////////////////////////////////////////////////////////
	
	// Get the sf::Color from a color table entry. The sf::Color is created by
	//		looking for the values of RGBA, each with the value of 0 to 255. Any
	//		value not specified is assumed to be zero. Any value not in the
	//		range of 0 to 255 will be wrapped back to a valid value
	// table - Table to load the values from. The values will be loaded from the
	//		values of RGBA
	// returns: The sf::Color the color table represent
	sf::Color getSfColor(const sol::table& table) const;

	// Vars ////////////////////////////////////////////////////////////////////
};

#endif
