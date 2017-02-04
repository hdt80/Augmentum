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
	color.r = table.get<int>("R");
	color.g = table.get<int>("G");
	color.b = table.get<int>("B");
	color.a = table.get<int>("A");

	return color;
}
