#include "gui_style/GuiEntryStyle.h"

#include "Database.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GuiEntryStyle::GuiEntryStyle(const sol::table& table)
	: GuiStyle("GuiEntryStyle") {
	
	readFromTable(table);
}

GuiEntryStyle::GuiEntryStyle()
	: GuiStyle("GuiEntryStyle"),
		_font(nullptr), _bodyColor(sf::Color::Transparent),
		_borderColor(sf::Color::Transparent),
		_textColor(sf::Color::Transparent),
		_highlightedColor(sf::Color::Transparent),
		_highlightedBorderColor(sf::Color::Transparent),
		_highlightedTextColor(sf::Color::Transparent),
		_dimensions(Vector2(0.0f, 0.0f)),
		_borderSize(0.0f), _padding(0), _textSize(0) {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void GuiEntryStyle::readFromTable(const sol::table& table) {
	// Because Database::get returns a const reference, and we need a pointer
	// we take away that constness. We should never ever modify _font once
	// we do this, or else undefined behaviour occurs
	_font = const_cast<sf::Font*>
		(&Databases::FontDatabase.get(table.get<std::string>("fontName")));

	_bodyColor = getSfColor(table["bodyColor"]);
	_borderColor = getSfColor(table["borderColor"]);
	_textColor = getSfColor(table["textColor"]);

	_highlightedColor = getSfColor(table["highlightedColor"]);
	_highlightedBorderColor = getSfColor(table["highlightedBorderColor"]);
	_highlightedTextColor = getSfColor(table["highlightedTextColor"]);

	_dimensions = Vector2(table["dimensions"]["X"], table["dimensions"]["X"]);

	_borderSize = table.get<float>("borderSize");
	_padding = table.get<int>("padding");
	_textSize = table.get<int>("textSize");
}

////////////////////////////////////////////////////////////////////////////////
// Static methods
////////////////////////////////////////////////////////////////////////////////

void GuiEntryStyle::loadFromFile(const std::string& filePath) {
	sol::state lua;

	try {
		lua.script_file(filePath);
	} catch (const sol::error& e) {
		CORE_ERROR("Failed to find file %s", filePath.c_str());
		return;
	}

	sol::table table = lua["GuiEntryStyle"];
	if (!table.valid()) {
		return;
	}

	auto iter = table.begin();
	while (iter != table.end()) {
		CORE_INFO("key: %s", (*iter).first.as<std::string>().c_str());

		std::string key = (*iter).first.as<std::string>();
		sol::table val = (*iter).second.as<sol::table>();

		++iter;

		GuiEntryStyle style;
		style.readFromTable(val);
		Databases::GuiEntryStyleDatabase.store(key, style);
	}
}
