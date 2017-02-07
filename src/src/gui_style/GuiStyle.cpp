#include "gui_style/GuiStyle.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GuiStyle::GuiStyle(const std::string& name)
	: LuaConfigEntry(name) {
	
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

sf::Color GuiStyle::getSfColor(const sol::table& table) const {
	sf::Color color;

	if (!table.valid()) {
		CORE_ERROR("Passed table is invalid. Returning default sf::Color");
		return color;
	}

	// Default to black
	color.r = table.get_or("R", 0);
	color.g = table.get_or("G", 0);
	color.b = table.get_or("B", 0);
	color.a = table.get_or("A", 255);

	return color;
}
