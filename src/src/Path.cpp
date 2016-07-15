#include "Path.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor and deconstuctor
///////////////////////////////////////////////////////////////////////////////
Path::Path() { 
	points.clear();
}

Path::~Path() {}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////

// Add a new point to the end of the path
void Path::addPoint(float x, float y) {
	Vector2* p = new Vector2(x, y);
	points.push_back(p);
}

// Return a point at a specifed index, or if it's outside the range return null
Vector2* Path::getPoint(unsigned int index) {
	if (index < 0 || index >= points.size()) {
		return nullptr;
	}
	return points[index]; 
}