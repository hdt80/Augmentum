#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Window;

class GuiComponent : public sf::Drawable, public sf::Transformable {
public:
	// GuiComponent ctor
	// pos - Where on the screen this component should start (pixels)
	// size - How much of the screen this component takes up (pixels)
	// windowSize - Size of the window this component is a part of
	GuiComponent(Window* window, Vector2 pos, Vector2 size, Vector2 windowSize);
	~GuiComponent();

	// Update this component based on how many milliseconds have passed
	void virtual update(int diff);
	void draw(sf::RenderTarget&, sf::RenderStates) const;

	// Resize this component to a newSize of a window. This should be called
	// after the Window this GuiComponent is a part of is resized
	void resize(Vector2 newSize);

	// Return if a point is within the bounds of this GuiComponent
	// x - X position of the window
	// y - Y position of the window
	bool contains(float x, float y);

	// Return if the point given is within the bounds of this GuiComponent, 
	//		but only if it's clickable
	// x - X position of the point clicked
	// y - Y position of the point clicked
	bool hasClicked(float x, float y);

	// Events
	
	// Called when this GuiComponent is clicked
	// window_x - X position of the click relative to the window
	// window_y - Y position of the click relative to the window
	// view_x - X position of the click relative to the view
	// view_y - Y position of the click relative to the view
	virtual void onClick(int button, float window_x, float window_y,
					     float view_x, float view_y) {}

	// Position getters and setters
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

	// Window
	void setWindow(Window* window);
	Window* getWindow() const;

	// Get the view representing this GuiComponent
	sf::View getView() { return _view; }

	// Updating getter and setter
	bool isUpdating() const { return _updating; }
	void setUpdating(bool b) { this->_updating = b; }

	bool isVisible() const { return _visible; }
	void setVisible(bool b) { this->_visible = b; }

	bool isClickable() const { return _clickable; }
	void setClickable(bool b) { this->_clickable = b; }

protected:
	GuiComponent();

	Vector2 _pos; // Position of this component
	Vector2 _size; // Dimension of the component. x = width, y = height

	bool _visible; // If this component is visible
	bool _updating; // If we should update this component
	bool _clickable; // If this GuiComponent can be clicked

	sf::View _view;

	Window* _window;
};


#endif
