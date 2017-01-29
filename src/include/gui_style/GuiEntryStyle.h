#ifndef _GUI_STYLES_H
#define _GUI_STYLES_H

#include <SFML/Graphics.hpp>

#include "gui_style/GuiStyle.h"

#include "Vector2.h"

// GuiStyle that represents how a GuiEntry will be drawn when its put into
// a GuiComponent
class GuiEntryStyle : public GuiStyle {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// GuiEntryStyle ctor
	// table - Table to load all the values from. The table can have the
	//		follwing values. If any value is not specified the default value
	//		is loaded.
	//
	//		NOTE: A color table is a sub table from the table passed in which is
	//		used to represent a sf::Color. A color table will look for the
	//		values of RGBA, with ints from 0 to 255. If any of the RGBA values
	//		are not found, a default value of 0 will be assumed.
	//
	//		fontName: string - Name of the font to load from Database
	//		bodyColor: color table - Color to draw the body of the GuiEntry
	//		borderColor: color table - Color of the border around the body
	//		textColor: color table - Color to draw the text in the GuiEntry
	//		highlightedColor: color table - Color to draw the GuiEntry as when
	//			the GuiEntry is highlighted
	//		highlightedBorderColor: color table - Color to draw the border of
	//			the GuiEntry when the GuiEntry is highlighted
	//		highlightedTextColor: color table - Color to draw the text when
	//			the GuiEntry is highlighted
	//		dimensions: table - The table will contain 2 values, X and Y. Any
	//			value not provided will be assumed to be a zero
	//		borderSize: float - How many pixels to draw the border
	//		padding: int - How many pixels in between each GuiEntry that is in
	//			the same GuiComponent.
	//		textSize: int - Size of the text that is drawn in the GuiEntry
	GuiEntryStyle(const sol::table& table);

	// Nullary ctor. All the values are initalized to 0 and the font pointer
	//		is assigned to nullptr. This is needed so Database can initiate
	//		the default properly
	GuiEntryStyle();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Load all the value from a sol::table, the table should have the same
	//		name as _name
	// table - Table to load the values from
	virtual void readFromTable(const sol::table& table);

	// Value getters ///////////////////////////////////////////////////////////
	
	// No setters are provided because once a style is defined it shouldn't be
	// changed after its loaded. Doing so would cause all the GuiEntryies that
	// use the GuiEntryStyle to be using the wrong values, as the GuiEntry is
	// set up with a GuiEntryStyle, but does not store its values and cannot
	// update to match a changed GuiEntryStyle

	// Get the sf::Font used by the GuiEntryStyle
	// returns: _font
	inline const sf::Font* getFont() const { return _font; }

	// Get the color the body of the GuiEntry is drawn as
	// returns: _bodyColor
	inline const sf::Color& getBodyColor() const { return _bodyColor; }

	// Get the color the border of the GuiEntry is drawn as
	// returns: _borderColor
	inline const sf::Color& getBorderColor() const { return _borderColor; }

	// Get the color of the text that the GuiEntry is drawn with
	// returns: _textColor
	inline const sf::Color& getTextColor() const { return _textColor; }

	// Get the color the GuiEntry will be drawn when highlighted
	// returns: _highlightedColor
	inline const sf::Color& getHighlightedColor() const {
		return _highlightedColor; }

	// Get the color the border of a highlighted GuiEntry is drawn as
	// returns: _highlightedBorderColor
	inline const sf::Color& getHighlightedBorderColor() const {
		return _highlightedBorderColor; }

	// Get the color the text of a highlighted GuiEntry is drawn as
	// returns: _highlightedTextColor
	inline const sf::Color& getHighlightedTextColor() const {
		return _highlightedTextColor; }

	// Get the dimensions of each GuiEntry
	// returns: _dimensions
	inline const Vector2& getDimensions() const { return _dimensions; }

	// Get the size of the border that the GuiEntry is drawn with
	// returns: _borderSize
	inline float getBorderSize() const { return _borderSize; }

	// Get the padding inbetween each GuiEntry
	// returns: _padding
	inline int getPadding() const { return _padding; }

	// Get the size that the text of a GuiEntry is drawn with
	// returns: _textSize
	inline int getTextSize() const { return _textSize; }

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	// Font to use when drawing the text. _font must be a pointer and not a 
	// reference to avoid allocating a sf::Font before its assigned, as SFML
	// says creating a sf::Font is very resource heavy
	sf::Font* _font;

	sf::Color _bodyColor; // Background color
	sf::Color _borderColor; // Color around the border
	sf::Color _textColor; // Color of the text

	sf::Color _highlightedColor; // Color of highlighted entry
	sf::Color _highlightedBorderColor; // Color of the border's highlighted entry
	sf::Color _highlightedTextColor; // Color of highlighted entry's text

	Vector2 _dimensions; // How big each GuiEntry should be

	float _borderSize; // How big the border is in pixels
	int _padding; // Pixels between each GuiEntry
	int _textSize; // Size of the message if negative, automatically find it
};

#endif
