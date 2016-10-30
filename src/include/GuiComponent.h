#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GuiEntry.h"

class Window;

// Parameters to use when creating a GuiEntry
struct GuiEntryStyle {
	sf::Font* font; // Font to use

	sf::Color bodyColor; // Background color
	sf::Color borderColor; // Color around the border
	sf::Color textColor; // Color of the text

	sf::Color highlightedColor; // Color of highlighted entry
	sf::Color highlightedBorderColor; // Color of the border's highlighted entry
	sf::Color highlightedTextColor; // Color of highlighted entry's text

	Vector2 dimensions; // How big each GuiEntry should be

	float borderSize; // How big the border is in pixels
	int padding; // Pixels between each GuiEntry
	int textSize; // Size of the message if negative, automatically find it
};

// Parameters to use when drawing a GuiComponent
struct GuiComponentStyle {
	sf::Color bodyColor; // Background color
	sf::Color borderColor; // Color of the border
	
	float borderSize; // Pixels
};

class GuiComponent : public sf::Drawable, public sf::Transformable {
public:
	// GuiComponent ctor
	// window - Window this GuiComponent is being drawn to
	// entryStyle - How to draw the GuiEntries in this GuiComponent
	// compStyle - How to draw the background of this GuiComponent
	// pos - Where on the screen this component should start (pixels)
	// size - How much of the screen this component takes up (pixels)
	GuiComponent(Window* window, const GuiEntryStyle* entryStyle,
			const GuiComponentStyle* compStyle, Vector2 pos, Vector2 size);
	// Dtor, remember to define each dtor in an inherited
	virtual ~GuiComponent();

	// Methods ////////////////////////////////////////////////////////////////

	// Update this component based on how many microseconds have passed
	void virtual update(int diff);

	// Inherited from sf::Drawable
	void draw(sf::RenderTarget&, sf::RenderStates) const;

	// Resize this component to a newSize of a window. This should be called
	// after the Window this GuiComponent is a part of is resized
	void resize(Vector2 newSize);

	// Return if a point is within the bounds of this GuiComponent
	// x - X position of the window
	// y - Y position of the window
	virtual bool contains(float x, float y);

	// Return if the point given is within the bounds of this GuiComponent,
	//		but only if it's clickable
	// x - X position of the point clicked
	// y - Y position of the point clicked
	virtual bool hasClicked(float x, float y);

	// GuiEntry methods ////////////////////////////////////////////////////////

	// Add a new GuiEntry at a position
	// entry - GuiEntry to add
	// x - X position to put it. Relative to this view
	// y - Y position to put it. Relative to this view
	virtual void addEntry(GuiEntry* entry, float x = 0, float y = 0);

	// Get a GuiEntry at a position
	// x - X position to find the GuiEntry at
	// y - Y position to find the GuiEntry at
	virtual GuiEntry* getEntry(float x, float y);

	// Get the GuiStyle that this GuiComponent uses
	const GuiEntryStyle* getEntryStyle() { return _guiEntryStyle; }

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
	
	// Position of the GuiComponent relative to the Window
	Vector2 getPos() { return _pos; }
	float getX() { return _pos.X; }
	float getY() { return _pos.Y; }

	void setPosition(Vector2 pos) { this->_pos = pos; }
	void setX(float x) { _pos.X = x; }
	void setY(float y) { _pos.Y = y; }

	// Size getting and setters
	float getWidth() const { return _size.X; }
	float getHeight() const { return _size.Y; }
	Vector2 getSize() const { return _size; }

	void setSize(Vector2 size) { this->_size = size; } 
	void setWidth(float w) { _size.X = w; }
	void setHeight(float h) { _size.Y = h; }

	// Window getter and setter
	void setWindow(Window* window) { _window = window; }
	const Window* getWindow() { return _window; }

	// Get the view representing this GuiComponent
	// returns: _view
	sf::View getView() { return _view; }

	// Updating getter and setter //////////////////////////////////////////////
	
	bool isUpdating() const { return _updating; }
	void setUpdating(bool b) { this->_updating = b; }

	bool isVisible() const { return _visible; }
	void setVisible(bool b) { this->_visible = b; }

	bool isClickable() const { return _clickable; }
	void setClickable(bool b) { this->_clickable = b; }

protected:
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

#endif
