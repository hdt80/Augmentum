#ifndef _GUI_ENTRY_H
#define _GUI_ENTRY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Vector2.h"

class GuiComponent;
class GuiEntryStyle;

class GuiEntry : public sf::Drawable {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// GuiEntry ctor - After this object is created is will not change
	// guiComp - GuiComponent this GuiEntry is a part of. Values like the
	//		GuiEntryStyle or the origin will be gotten from this
	// msg - Message to display on the screen
	GuiEntry(GuiComponent* guiComp, const std::string& msg);

	// GuiEntry dtor
	virtual ~GuiEntry();

	// Methods /////////////////////////////////////////////////////////////////

	// Update the GuiEntry
	// diff - Microseconds since the last update
	// Most GuiEntries don't need to worry about this
	virtual void update(int diff) {}

	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	// Get the shape that will be drawn in a GuiComponent
	// returns: _shape
	inline const sf::RectangleShape& getShape() const { return _shape; }

	// Get the text object that will be drawn in a GuiComponent
	// returns: _text
	const sf::Text& getText() const { return _text; }

	// Get the message of this object
	// returns: _msg
	const std::string& getMessage() const { return _msg; }

	// Set if this GuiEntry is highlighted
	// b - If this GuiEntry is highlighted
	void setHighlighted(bool b);

	// Change the message drawn to the screen
	// msg - New message to be drawn
	void setMessage(const std::string& msg);

	// Set the position of the GuiEntry
	// x - X coord relative to the GuiComponent's origin
	// y - Y coord relative to the GuiComponent's origin
	virtual void setPosition(float x, float y);

	// Position methods ////////////////////////////////////////////////////////

	// Get the x position relative to the screen
	// returns: Where the GuiEntry is relative to the screen
	inline float getX() const { return getOriginX() + _shape.getPosition().x; }

	// Get the y position relative to the screen
	// returns: Where the GuiEntry is relative to the screen
	inline float getY() const { return getOriginY() + _shape.getPosition().y; }

	// Get the x component of where the GuiEntry's origin is
	// returns: _origin.X
	inline float getOriginX() const { return _origin.X; }

	// Get the y component of where the GuiEntry's origin is
	// returns: _origin.Y
	inline float getOriginY() const { return _origin.Y; }

	// Does this GuiEntry contain the points x and y
	// x - X coord to check
	// y - Y coord to check
	// returns: If this GuiEntry contains the points
	bool contains(float x, float y) const;

	// Get the GuiEntryStyle used in this GuiEntry
	// returns: Pointer to the style used in this GuiEntry
	inline const GuiEntryStyle* getStyle() const { return _style; }

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	const GuiEntryStyle* _style; // Style to draw the GuiEntry as

	const GuiComponent* _comp; // GuiComponent this GuiEntry is a part of

	sf::RectangleShape _shape; // Drawn to the screen
	sf::Text _text; // Drawn to the screen

	std::string _msg; // What message will be drawn

	Vector2 _origin; // Position of the GuiComponent the GuiEntry is in

	bool _highlighted; // Is this GuiEntry highlighted
};

#endif
