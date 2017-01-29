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
