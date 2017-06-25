#include "game/gui_style/GuiComponentStyle.h"

#include "game/Game.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GuiComponentStyle::GuiComponentStyle(const sol::table& table)
	: GuiStyle("GuiComponentStyle") {

	readFromTable(table);
}

GuiComponentStyle::GuiComponentStyle()
	: GuiStyle("GuiComponentStyle"),
		_bodyColor(sf::Color::Transparent),
		_borderColor(sf::Color::Transparent), _borderSize(0.0f) {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void GuiComponentStyle::readFromTable(const sol::table& table) {
	_bodyColor = getSfColor(table["bodyColor"]);
	_borderColor = getSfColor(table["borderColor"]);

	_borderSize = table.get<float>("borderSize");
}
