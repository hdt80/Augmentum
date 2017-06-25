#include "game/gui_style/GuiProgressBarStyle.h"

#include "game/Game.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GuiProgressBarStyle::GuiProgressBarStyle(const sol::table& table)
	: GuiStyle("GuiProgressBarStyle") {

	readFromTable(table);
}

GuiProgressBarStyle::GuiProgressBarStyle()
	: GuiStyle("GuiProgressBarStyle"),
		_minColor(sf::Color::Transparent),
		_maxColor(sf::Color::Transparent),
		_outlineColor(sf::Color::Transparent),
		_backgroundColor(sf::Color::Transparent), _vert(false) {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void GuiProgressBarStyle::readFromTable(const sol::table& table) {
	_minColor = getSfColor(table["minColor"]);
	_maxColor = getSfColor(table["maxColor"]);
	_outlineColor = getSfColor(table["outlineColor"]);
	_backgroundColor = getSfColor(table["backgroundColor"]);

	_vert = table.get<bool>("vertical");
}
