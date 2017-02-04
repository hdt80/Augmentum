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
