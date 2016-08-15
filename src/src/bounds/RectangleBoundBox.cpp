#include "bounds/RectangleBoundBox.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and Dtor
////////////////////////////////////////////////////////////////////////////////

RectangleBoundBox::RectangleBoundBox() {}

// RectangleBoundBox ctor
// origin - X and Y coords that mark the origin of this box, top left
// dims - Height and width of this box
RectangleBoundBox::RectangleBoundBox(Vector2 origin, Vector2 dims)
	: BoundBox(origin),
		_dimensions(dims) {

	// Add the points in clockwise fashion
	// 0--1
	// |  |
	// 3--2
	addPoint(Vector2(0.0f, 0.0f));
	addPoint(Vector2(0.0f, _dimensions.Y));
	addPoint(Vector2(_dimensions.X, _dimensions.Y));
	addPoint(Vector2(_dimensions.X, 0.0f));
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

// Check if a point is contained within this BoundBox
// x - X coord to check
// y - Y coord to check
bool RectangleBoundBox::contains(float x, float y) {
	return x >= getPoint(0).X && x <= getPoint(2).X
			&& y >= getPoint(0).Y && y <= getPoint(2).Y;
}
