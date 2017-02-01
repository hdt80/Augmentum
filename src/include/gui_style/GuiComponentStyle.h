#ifndef _GUI_COMPONENT_STYLE_H
#define _GUI_COMPONENT_STYLE_H

#include "gui_style/GuiStyle.h"

#include <SFML/Graphics.hpp>

class GuiComponentStyle : public GuiStyle {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// GuiComponentStyle ctor
	// table - Table to load all the values from. The table can have the
	//		follwing values. If any value is not specified the default value
	//		is loaded.
	//
	//		NOTE: A color table is a sub table from the table passed in which is
	//		used to represent a sf::Color. A color table will look for the
	//		values of RGBA, with ints from 0 to 255. If any of the RGBA values
	//		are not found, a default value of 0 will be assumed.
	//
	//		bodyColor: color table - Color to draw the background of the
	//			GuiComponent
	//		borderColor: color table - Color to draw the border of the
	//			GuiComponent as
	//		borderSize: float - Size of the border in pixesl
	GuiComponentStyle(const sol::table& table);

	// Nullary ctor required for Databases. The default valeus are loaded of
	//		sf::Color::Transparent for any sf::Color and 0 for any numeric value
	GuiComponentStyle();

	// Static methods //////////////////////////////////////////////////////////
	
	// Use a file to create the GuiStyles can be found from that file. Each
	//		GuiStyle will be found in a table with the name of the GuiStyle that
	//		is being loaded. For example, when loading GuiEntryStyles from the
	//		file "lua/gui_styles/GuiEntryStyles.lua", this method will look for
	//		the table "GuiEntryStyle". That table will contain valid entries
	//		that the GuiStyle that is being loaded can be created from. The
	//		sub tables found in the root table will be named what that loaded
	//		GuiStyle will be saved under in a Database
	// filePath - Path to the file that the GuiStyles will be loaded from. The
	//		path is relative to the program's current working directory. This
	//		should include the file extension.
	static void loadFromFile(const std::string& filePath) {
		sol::state lua;

		try {
			lua.script_file(filePath);
		} catch (const sol::error& e) {
			CORE_ERROR("Failed to find file %s", filePath.c_str());
			return;
		}

		sol::table table = lua["GuiComponentStyle"];
		if (!table.valid()) {
			return;
		}

		auto iter = table.begin();
		while (iter != table.end()) {
			CORE_INFO("key: %s", (*iter).first.as<std::string>().c_str());

			sol::table val = (*iter).second.as<sol::table>();

			++iter;

			auto titer = val.begin();
			while (titer != val.end()) {
				CORE_INFO("tkey: %s", (*titer).first.as<std::string>().c_str());
				++titer;
			}

		}
	}
	
	// Methods /////////////////////////////////////////////////////////////////
	
	// Load all the value from a sol::table, the table should have the same
	//		name as _name
	// table - Table to load the values from
	void readFromTable(const sol::table& table);
	
	// Get the color that the body of the GuiComponent is drawn as
	// returns: _bodyColor
	inline const sf::Color& getBodyColor() const { return _bodyColor; }

	// Get the border color that the GuiComponent will be drawn with
	// returns: _borderColor
	inline const sf::Color& getBorderColor() const { return _borderColor; }

	// Get the size of the border in pixels inbetween GuiEntries in the
	//		GuiComponent
	// returns: _borderSize
	inline float getBorderSize() const { return _borderSize; }

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	sf::Color _bodyColor;
	sf::Color _borderColor;

	float _borderSize;
};

#endif
