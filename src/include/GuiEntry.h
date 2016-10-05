#ifndef _GUI_ENTRY_H
#define _GUI_ENTRY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Vector2.h"

struct GuiEntryStyle;

class GuiEntry : public sf::Drawable {
public:
	// GuiEntry ctor - After this object is created is will not change
	// style - Style to model the _shape and _text after
	// origin - Where the GuiComponent that this is a part of is at
	// msg - Message to display on the screen
	GuiEntry(const GuiEntryStyle* style,
			Vector2 origin, const std::string& msg);
	virtual ~GuiEntry();

	// Update the GuiEntry
	// diff - Microseconds since the last update
	// Most GuiEntries don't need to worry about this
	virtual void update(int diff) {}

	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	// Get the shape that will be drawn in a GuiComponent
	const sf::RectangleShape& getShape() { return _shape; }
	// Get the text object that will be drawn in a GuiComponent
	const sf::Text& getText() { return _text; }
	// Get the message of this object
	const std::string& getMessage() { return _msg; }

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

	// Get position
	// These 2 are the absolute position relative to the screen
	inline float getX() { return getOriginX() + _shape.getPosition().x; }
	inline float getY() { return getOriginY() + _shape.getPosition().y; }

	// Get where the origin of the GuiComp is
	inline float getOriginX() { return _origin.X; }
	inline float getOriginY() { return _origin.Y; }

	// Does this GuiEntry contain the points x and y
	// x - X coord to check
	// y - Y coord to check
	bool contains(float x, float y);

protected:
	const GuiEntryStyle* _style;
	sf::RectangleShape _shape; // Drawn to the screen
	sf::Text _text; // Drawn to the screen
	std::string _msg; // What message will be drawn
	bool _highlighted; // Is this GuiEntry highlighted
	Vector2 _origin; // Where this GuiEntry is relative to the GuiComponent
};

#endif
