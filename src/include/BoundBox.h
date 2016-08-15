#ifndef _BOUND_BOX_H
#define _BOUND_BOX_H

#include "Vector2.h"
#include <vector>
#include "Logger.h"

class BoundBox {
public:
	// nullary ctor
	BoundBox() {}
	BoundBox(Vector2 origin);
	virtual ~BoundBox() {}

	// Check if a point is contained within this bounding box
	// point - Point to check
	virtual bool contains(Vector2 point) { return contains(point.X, point.Y); }

	// Check if a point is contained within this bounding box
	// x - X coord to check
	// y - Y coord to check
	virtual bool contains(float x, float y) { CORE_INFO("A");return false; }

	// Check if this BoundBox intersects another BoundBox
	virtual bool intersects(BoundBox* box);

	// Get the rotation of this bounding box in degrees
	virtual float getRotation() { return _rotation; }
	// Set the rotation of the bounding box, in degrees
	// f - Rotation of this bounding box, in degrees
	virtual void setRotation(float f) { _rotation = f; }

	// Origin setters
	
	// Set the origin to a specific point
	// v - Absolute point to set the origin to
	// x - Absolute x coord to set the origin to
	// y - Absolute y coord to set the origin to
	virtual void setOrigin(Vector2 v) { _origin = v; }
	virtual void setOrigin(float x, float y) { _origin.X = x; _origin.Y = y; }

	// Get the origin of this point
	virtual const Vector2& getOrigin() { return _origin; }

	// Get the amount of points this BoundBox has
	virtual unsigned int getPointCount() { return _points.size(); }

	// Get a certain point. Used to find the absolute position of the points
	// index - Index of the point to get that's stored in _points
	Vector2 getPoint(int index);

protected:
	// Add a point to the points that define this BoundBox
	// v - Vector to add
	void addPoint(Vector2 v);

	// Get a certain point. Used to find the absolute position of the points
	// index - Index of the point to get that's stored in _points
	//Vector2 getPoint(int index);

	// The points that define where this BoundBox. These are not absolute 
	// coords, but relative coords, relaitve to the _origin
	std::vector<Vector2> _points;

	Vector2 _origin; // Where this BoundBox is located at

	float _rotation; // 0 is straight up. 90 is to the right, measured in degs
};

#endif
