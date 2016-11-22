#ifndef _TARGET_H
#define _TARGET_H

#include "Vector2.h"

class Target {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Target ctor
	// x - X pos
	// y - Y pos
	Target(float x, float y)
		: x(x), y(y) {}

	// Target ctor
	// v - Vector to create Target from
	Target(Vector2 v)
		: x(v.X), y(v.Y) {}

	// Target ctor
	// v - Vector to create Target from
	Target(Vector2* v)
		: x(v->X), y(v->Y) {}

	// Target dtor
	virtual ~Target(){}

	// Methods /////////////////////////////////////////////////////////////////

	// Get the euclidean distance from a point
	// dx - X point to compare
	// dy - Y point to compare
	// returns: The Euclidean distance from that point
	float distanceWith(float dx, float dy);

	// Get the euclidean distance from a Target
	// t - Target to compar to
	// returns: The Euclidean distance from that Target
	float distanceWith(Target* t);

	// Get the euclidean distance squared from a point
	// dx - X point to compare
	// dy - Y point to compare
	// returns: The Euclidean distance from that point
	float distanceWithSqr(float dx, float dy);
	
	// Get the euclidean distance squared from a Target
	// t - Target to compar to
	// returns: The Euclidean distance from that Target
	float distanceWithSqr(Target* t);

	// Get the position of this Target
	// returns: A Vector representing the position of this Target
	virtual Vector2 getPosition() const { return Vector2(x, y); }

	// Get the X coord of this Target
	// returns: x
	virtual float getX() const { return x; }

	// Get the Y coord of this Target
	// returns: y
	virtual float getY() const { return y; }

	// Set the position of this Target
	// x - X coord to set
	// y - Y coord to set
	virtual void setPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}
	
	// See if this is a simple Target
	// returns: true
	virtual bool isSimpleTarget() { return true; }

protected:
	float x; // X component of this Target
	float y; // Y component of this Target
};

#endif
