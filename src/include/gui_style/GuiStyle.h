#ifndef _GUI_STYLE_H
#define _GUI_STYLE_H

#include "LuaConfigEntry.h"

#include <SFML/Graphics.hpp>

#include "Logger.h"

class GuiStyle : public LuaConfigEntry {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// GuiStyle ctor
	// name - Name of the LuaConfigEntry that the values will be loaded from
	GuiStyle(const std::string& name);

	// Static methods //////////////////////////////////////////////////////////
	
	// Use a file to create the GuiStyles can be found from that file. Each
	//		GuiStyle will be found in a table with the name of the GuiStyle that
	//		is being loaded. For example, when loading GuiEntryStyles from the
	//		file "lua/gui_styles/GuiEntryStyles.lua", this method will look for
	//		the table "GuiEntryStyle". That table will contain valid entries
	//		that the GuiStyle that is being loaded can be created from. The
	//		sub tables found in the root table will be named what that loaded
	//		GuiStyle will be saved under in a Database
	// template T - Type that is being loaded. This is needed so we can pass
	//		the Database of <T> that the loaded GuiStyles are being stored into
	// filePath - Path to the file that the GuiStyles will be loaded from. The
	//		path is relative to the program's current working directory. This
	//		should include the file extension.
	// typeName - Name of the type to load from. This is the name of the root
	//		table all the sub tables are iterated for
	// returns: A std::map of each loaded GuiStyle. The key is the name the
	//		sub table was found under. The value is the loaded GuiStyle
	//		that was loaded
	template<typename T>
	static std::map<std::string, T> loadFromFile(const std::string& filePath,
		const std::string& typeName) {
//
//		sol::state lua;
//		std::map<std::string, T> loaded;
//
//		if (!lua.load_file(filePath)) {
//			CORE_ERROR("Failed to find file %s", filePath.c_str());
//			return loaded;
//		}
//
//		sol::table table = lua[typeName];
//
//		for (auto iter : table) {
//			CORE_INFO("%s:%s", iter.first, iter.second);
//		}
//
//		return loaded;
	}

	// Methods /////////////////////////////////////////////////////////////////
	
	// Load all the value from a sol::table, the table should have the same
	//		name as _name
	// table - Table to load the values from
	virtual void readFromTable(const sol::table& table) {};
	
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
