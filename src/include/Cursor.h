#ifndef _CURSOR_H
#define _CURSOR_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Cursor : public sf::Drawable {
public:
	Cursor();
	~Cursor();

	// Getting the position of the Cursor
	float getX() { return _x; }
	float getY() { return _y; }

	// Setting the position of the Cursor
	void setPosition(float x, float y);
	void setX(float x) { setPosition(x, getY()); }
	void setY(float y) { setPosition(getX(), y); }

	// The VertexArray to draw as the Cursor
	void setVertexArray(sf::VertexArray varray) { _vertArray = varray; }
	const sf::VertexArray& getVertexArray() { return _vertArray; }

	// Update the Cursor
	// diff - Time since last called in microseconds
	void update(int diff);

	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

private:
	sf::VertexArray _vertArray;

	// Position of the Cursor
	float _x;
	float _y;
};

#endif
