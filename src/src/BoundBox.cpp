#include "BoundBox.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor
////////////////////////////////////////////////////////////////////////////////

BoundBox::BoundBox(Vector2 origin) {
	_origin = origin;
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

// Add a point to the points that define this BoundBox
// v - Point to add
void BoundBox::addPoint(Vector2 v) {
	_points.push_back(v);
}

// Check if this BoundBox intersects with another BoundBox
// box - Box to check for intersections with
bool BoundBox::intersects(BoundBox* box) {
	for (unsigned int i = 0; i < getPointCount(); ++i) {
		if (box->contains(getPoint(i))) {
			return true;
		}
	}
	return false;
}

// Get a certain point. This returns the absolute position of a point 
// index - Index of the point stored in _points
Vector2 BoundBox::getPoint(int index) {
	return Vector2(_points[index] + _origin);
}
