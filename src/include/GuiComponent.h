#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class GuiComponent : public sf::Drawable, public sf::Transformable {
public:
	GuiComponent(Vector2 pos, Vector2 size, Vector2 windowSize);
	~GuiComponent();

	// Update this component based on how many milliseconds have passed
	void virtual update(int diff);
	void draw(sf::RenderTarget&, sf::RenderStates) const;

	void resize(Vector2 newSize);

	// Position getters and setters
	float getX() { return _pos.X; }
	float getY() { return _pos.Y; }
	void setPosition(Vector2 pos) { this->_pos = pos; }
	void setX(float x) { _pos.X = x; }
	void setY(float y) { _pos.Y = y; }

	// Size getting and setters
	float getWidth() { return _size.X; }
	float getHeight() { return _size.Y; }
	Vector2 getSize() const { return _size; }
	void setSize(Vector2 size) { this->_size = size; } 
	void setWidth(float w) { _size.X = w; }
	void setHeight(float h) { _size.Y = h; }

	sf::View getView() { return _view; }

	bool isUpdating() { return _updating; }
	void setUpdating(bool b) { this->_updating = b; }

	bool isVisible() { return _visible; }
	void setVisible(bool b) { this->_visible = b; }

protected:
	GuiComponent();

	Vector2 _pos; // Position of this component
	Vector2 _size; // Dimension of the component. x = width, y = height

	bool _visible; // If this component is visible
	bool _updating; // If we should update this component

	sf::View _view;
};


#endif
