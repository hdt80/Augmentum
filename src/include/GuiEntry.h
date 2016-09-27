#ifndef _GUI_ENTRY_H
#define _GUI_ENTRY_H

#include <SFML/Graphics.hpp>
#include <string>

struct GuiStyle;

class GuiEntry {
public:
	GuiEntry();
	// GuiEntry ctor - After this object is created is will not change
	// style - Style to model the _shape and _text after
	// msg - Message to display on the screen
	GuiEntry(GuiStyle* style, const std::string& msg);
	~GuiEntry();

	// Get the shape that will be drawn in a GuiComponent
	const sf::RectangleShape& getShape() { return _shape; }
	// Get the text object that will be drawn in a GuiComponent
	const sf::Text& getText() { return _text; }
	// Get the message of this object
	const std::string& getMessage() { return _msg; }

	// Change the message drawn to the screen
	// msg - New message to be drawn
	void setMessage(const std::string& msg);

	// Set the position of the GuiEntry
	// x - X coord relative to the GuiComponent's origin
	// y - Y coord relative to the GuiComponent's origin
	void setPosition(float x, float y);

protected:
	sf::RectangleShape _shape; // Drawn to the screen
	sf::Text _text; // Drawn to the screen
	std::string _msg; // What message will be drawn
};

#endif
