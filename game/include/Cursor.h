#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Cursor : public sf::Drawable {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Cursor ctor
	// window - Window the Cursor is drawn to
	Cursor();

	// Cursot dtor
	~Cursor();

	// Methods /////////////////////////////////////////////////////////////////

	// Get the current x coord of the postion of the Cursor. This is relative to
	//		the window the Cursor is drawn in
	// returns: _x
	inline float getX() const { return _x; }

	// Get the current y coord of the postion of the Cursor. This is relative to
	//		the window the Cursor is drawn in
	// returns: _y
	inline float getY() const { return _y; }

	// Set the position of the Cursor relative to the current Window
	// x - X coord of the Cursor
	// y - Y coord of the Cursor
	void setPosition(float x, float y);

	// Set the X position of the Cursor relative to the current Window
	// x - X coord to set
	inline void setX(float x) { setPosition(x, getY()); }
	
	// Set the Y position of the Cursor relative to the current Window
	// y - Y coord to set
	inline void setY(float y) { setPosition(getX(), y); }

	// Set the sf::VertexArray used to draw the Cursor
	// varray - sf::VertextArray that will be drawn to represent the Cursor
	inline void setVertexArray(sf::VertexArray varray) { _vertArray = varray; }

	// Get the sf::VertexArray used to draw the Cursor
	// returns: _vertArray
	inline const sf::VertexArray& getVertexArray() const { return _vertArray; }

	// Update the Cursor
	// diff - Time since last called in microseconds
	void update(int diff);

	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

private:
	// Vars ////////////////////////////////////////////////////////////////////
	
	// Two sf::VertexArrays are used to draw the Cursor. _vertArray is the
	// sf::VertexArray that is drawn to the sf::RenderTarget, while _origArray
	// is the original sf::VertexArray that the Cursor draws. _vertArray's
	// position changes when calling setPosition(), which uses _origArray
	// to know where to draw the new points
	sf::VertexArray _vertArray;
	sf::VertexArray _origVert;

	// Position of the Cursor relative to the Window being drawn to
	float _x;
	float _y;
};
