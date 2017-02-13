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
};

#endif
