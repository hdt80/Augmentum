#pragma once

#include "game/gui/GuiComponent.h"

class Map;

class WorldComponent : public GuiComponent {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// WorldComponent ctor
	// window - Window the WorldComponent is drawn in
	// style - Style to draw the GuiEntrys as
	// compStyle - Style to draw the WorldComponent as
	// pos - Position of the WorldComponent relative to the window
	// size - Size of the WorldComponent is pixels
	WorldComponent(Window* window, const GuiEntryStyle* style,
			const GuiComponentStyle* compStyle, Vector2 pos, Vector2 size);		

	// Methods /////////////////////////////////////////////////////////////////

	// Update the WorldComponent
	// diff - Microseconds to update for
	virtual void update(int diff);

	// Inherited from sf::Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Occurs when the GuiComponent is clicked
	// button - Button clicked. Use sf::Mouse::Button to compare
	// window_x - Where in the window the click happened
	// window_y - Where in the window the click happened
	// view_x - Where the click happened relative to the current view
	// view_y - Where the click happened relative to the current view
	virtual void onClick(int button, float window_x, float window_y,
		float view_x, float view_y);

	// Set if the bounds of the objects are currently being draw
	// b - To draw the bounds or not
	inline void setDrawBounds(bool b) { _drawBounds = b; }

	// Get if the bounding boxes of the Objects are currently being drawn
	// returns: _drawBounds
	inline bool getDrawBounds() const { return _drawBounds; }

private:
	bool _drawBounds; // Draw the bounding boxes of the Objects

	Map* _map;
};
