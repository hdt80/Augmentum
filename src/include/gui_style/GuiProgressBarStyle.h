#ifndef _GUI_PROGRESS_BAR_STYLE_H
#define _GUI_PROGRESS_BAR_STYLE_H

#include "gui_style/GuiStyle.h"

class GuiProgressBarStyle : public GuiStyle {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// GuiProgressBarStyle ctor
	// table - Table to load all the values from. The table can have the
	//		follwing values. If any value is not specified the default value
	//		is loaded.
	//
	//		NOTE: A color table is a sub table from the table passed in which is
	//		used to represent a sf::Color. A color table will look for the
	//		values of RGBA, with ints from 0 to 255. If any of the RGBA values
	//		are not found, a default value of 0 will be assumed.
	//
	//		minColor: color table - Color the draw the GuiProgressBar when the
	//			tracked value is equal to the minimum value
	//		maxColor: color table - Color to draw the GuiProgressBar when the
	//			tracked value is equal to the max value
	//		outlineColor: color table - Color the outline of the GuiProgressBar
	//		backgroundColor: color table - Color of the background
	//		vartical: bool - If the GuiProgressBar is a vertical bar or not
	GuiProgressBarStyle(const sol::table& table);

	// Nullary ctor used for Databases. The default values of for all the colors
	//		will be loaded as sf::Color::Transparent and any numerical value
	//		will be initalized to zero
	GuiProgressBarStyle();

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
	static void loadFromFile(const std::string& filePath);

	// Methods /////////////////////////////////////////////////////////////////
	
	// Load all the value from a sol::table, the table should have the same
	//		name as _name
	// table - Table to load the values from
	void readFromTable(const sol::table& table);

	// Get the color the GuiProgressBar will be drawn when the value tracked
	//		is equal to the minimum value
	// returns: _minColor
	inline const sf::Color& getMinColor() const { return _minColor; }

	// Get the color the GuiProgressBar will be drawn when the value tracked
	//		is equal to the max value
	// returns: _maxColor
	inline const sf::Color& getMaxColor() const { return _maxColor; }

	// Get the color the GuiProgressBar is outlined with
	// returns: _outlineColor
	inline const sf::Color& getOutlineColor() const { return _outlineColor; }

	// Get the color the GuiProgressBar's background is
	// returns: _backgroundColor
	inline const sf::Color& getBackgroundColor() const {
		return _backgroundColor; }

	// Get if the GuiProgressBar is vertical or not
	// returns: _vert
	inline bool isVertical() const { return _vert; }

protected:
	// Vars ////////////////////////////////////////////////////////////////////

	sf::Color _minColor; // Color to draw the bar when value = 0
	sf::Color _maxColor; // Color to draw the bar when value = 100
	sf::Color _outlineColor; // Color of the outline around the bar
	sf::Color _backgroundColor; // Color to fill when the bar isn't full

	bool _vert; // If the bar should be up/down  TODO: Add this
};

#endif


