#pragma once

#include "game/Vector2.h"
#include "game/gui/GuiEntry.h"
#include "game/gui_style/GuiEntryStyle.h"
#include "game/gui_style/GuiComponentStyle.h"

#include <SFML/Graphics.hpp>

class Window;

class GuiComponent : public sf::Drawable, public sf::Transformable {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// GuiComponent ctor
	// window - Window this GuiComponent is being drawn to
	// entryStyle - How to draw the GuiEntries in this GuiComponent
	// compStyle - How to draw the background of this GuiComponent
	// pos - Where on the screen this component should start (pixels)
	// size - How much of the screen this component takes up (pixels)
	GuiComponent(Window* window, const GuiEntryStyle* entryStyle,
		const GuiComponentStyle* compStyle, Vector2 pos, Vector2 size);

	// Dtor, remember to define each dtor in an inherited class
	virtual ~GuiComponent();

	// Methods ////////////////////////////////////////////////////////////////

	// Update this component based on how many microseconds have passed
	// diff - Microseconds to simulate the GuiEntry for
	void virtual update(int diff);

	// Inherited from sf::Drawable
	void draw(sf::RenderTarget&, sf::RenderStates) const;

	// Resize this component to a newSize of a window. This should be called
	// after the Window this GuiComponent is a part of is resized
	void resize(Vector2 newSize);

	// Return if a point is within the bounds of this GuiComponent
	// x - X position of the window
	// y - Y position of the window
	virtual bool contains(float x, float y) const;

	// Return if the point given is within the bounds of this GuiComponent,
	//		but only if it's clickable
	// x - X position of the point clicked
	// y - Y position of the point clicked
	virtual bool hasClicked(float x, float y) const;

	// GuiEntry methods ////////////////////////////////////////////////////////

	// Add a new GuiEntry at a position
	// entry - GuiEntry to add
	// x - X position to put it. Relative to this view
	// y - Y position to put it. Relative to this view
	virtual void addEntry(GuiEntry* entry, float x = 0, float y = 0);

	// Get a GuiEntry at a position
	// x - X position to find the GuiEntry at
	// y - Y position to find the GuiEntry at
	virtual GuiEntry* getEntry(float x, float y) const;

	// Get the GuiStyle that this GuiComponent uses
	// returns: _guiEntryStyle
	inline const GuiEntryStyle* getEntryStyle() const { return _guiEntryStyle; }

	// Events //////////////////////////////////////////////////////////////////
	
	// Called when this GuiComponent is clicked
	// button - Button that was pressed, use sf::Mouse::Button::* to compare
	// window_x - X position of the click relative to the window
	// window_y - Y position of the click relative to the window
	// view_x - X position of the click relative to the view
	// view_y - Y position of the click relative to the view
	virtual void onClick(int button, float window_x, float window_y,
		float view_x, float view_y);

	// Position getters and setters ////////////////////////////////////////////
	
	// Get the position of the GuiComponent relative to the Window
	// returns: _pos
	inline const Vector2& getPos() const { return _pos; }

	// Get the X coord of the position
	// returns: _pos.X
	inline float getX() const { return _pos.X; }

	// Get tye Y coord of the position
	// returns: _pos.Y
	inline float getY() const { return _pos.Y; }

	// Set the position of the GuiComponent
	// pos - New position of the GuiComponent relative to the Window
	void setPosition(const Vector2& pos) { _pos = pos; }

	// Set the X coord of the position of the GuiComponent
	// x - X coord to set
	inline void setX(float x) { _pos.X = x; }

	// Set the Y coord of the position of the GuiComponent
	// y - Y coord to set
	inline void setY(float y) { _pos.Y = y; }

	// Size getting and setters ////////////////////////////////////////////////
	
	// Get the width of the GuiComponent measured in pixels
	// returns: _size.X
	inline float getWidth() const { return _size.X; }

	// Get the height of the GuiComponent measured in pixels
	// returns: _size.Y
	inline float getHeight() const { return _size.Y; }

	// Get the size of the GuiComponent measured in pixels
	// returns: _size
	inline const Vector2& getSize() const { return _size; }

	// Set the size of the GuiComponent
	// size - New size in pixels to set the GuiComponent
	inline void setSize(Vector2 size) { this->_size = size; }

	// Set the width of the GuiComponent
	// w - New width in pixels of the GuiComponent
	inline void setWidth(float w) { _size.X = w; }

	// Set the neight of the GuiComponent
	// h - New height in pixels of the GuiComponent
	inline void setHeight(float h) { _size.Y = h; }

	// Window getter and setter ////////////////////////////////////////////////
	
	// Set the Window that the GuiComponent is drawn to
	// window - New Window to draw to
	inline void setWindow(Window* window) { _window = window; }

	// Get the Window the GuiComponent is drawn to
	inline const Window* getWindow() const { return _window; }

	// Get the view representing this GuiComponent
	// returns: _view
	inline sf::View getView() const { return _view; }

	// Updating getter and setter //////////////////////////////////////////////
	
	// Check if the GuiComponent is updating
	// returns: _updating
	inline bool isUpdating() const { return _updating; }

	// Set if the GuiComponent is updating
	// b = Is the GuiComponent updating?
	inline void setUpdating(bool b) { _updating = b; }

	// Check if the GuiComponent is visible
	// returns: _visible
	inline bool isVisible() const { return _visible; }

	// Set if the GuiComponent is visible
	// b - Is the GuiComponent visible?
	inline void setVisible(bool b) { this->_visible = b; }

	// Check if the GuiComponent can be clicked on
	// returns: _clickable
	inline bool isClickable() const { return _clickable; }

	// Set if the GuiComponent can be clicked on
	// b - Should the GuiComponent be clickable?
	inline void setClickable(bool b) { this->_clickable = b; }

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	Vector2 _pos; // Position of this component relative to the Window
	Vector2 _size; // Dimension of the component in pixels

	sf::RectangleShape _background; // Background to draw

	const GuiEntryStyle* _guiEntryStyle; // GuiStyle to use in this GuiComponent

	std::vector<GuiEntry*> _entries; // Entries to draw
	GuiEntry* _highlightedEntry; // Entry being hovered over

	bool _visible; // If this component is visible
	bool _updating; // If we should update this component
	bool _clickable; // If this GuiComponent can be clicked

	sf::View _view; // View to draw to

	Window* _window; // Window this GuiComponent is drawn to
};
