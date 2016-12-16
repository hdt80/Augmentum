#ifndef _MATH_UTIL_H
#define _MATH_UTIL_H

#include <vector>

#include "Box2D/Box2D.h"
#include "Vector2.h"

namespace MathUtil {

	// Constant of Pi
	const float PI = 3.14159265358979323846f;

	// Convert radians to degrees
	// rad - Angle in radians
	// returns: The equivalent angle in degrees
	inline float radToDeg(float rad) { return rad * 57.295779f; }

	// Convert degrees to radians
	// deg - Angle in degrees
	// returns: The equivalent angle in radians
	inline float degToRad(float deg) { return deg * 0.0174532f; }

	// Scale used between pixels and Box2D
	const float B2BOX_SCALE = 30.f;

	// Convert to Box2D's scale
	// f - Value to convert
	// returns: f in terms of Box2D's units
	inline float toB2(float f) { return f / B2BOX_SCALE; }

	// Convert from Box2D's scale
	// f - Value to convert
	// returns: f in terms of the units the game uses
	inline float fromB2(float f) { return f * B2BOX_SCALE; }

	// Linearly interpolate to a value
	// max - Max value to approach
	// cur - Current value 
	// dt - Deltatime, how much to interpolate
	float approach(float max, float cur, float dt);

	// Linearly interpolate to a value
	// max - Max value to approach
	// cur - Current value 
	// dt - Deltatime, how much to interpolate
	int linearInterpolate(float max, float cur, float dt);

	// Generate a regular polygon
	// sides - How many sides/corners the polygon should have
	// size - How many units accross the polygon should be
	// returns: A vector containing the points use to represent the polygon
	std::vector<b2Vec2> generatePolygon(int sides, float size);

	// Generate a non-regular convex polygon
	// sides - How many sides/corners the polygon should have
	// size - How many units accross the polygon should be
	// returns: A vector containing the points use to represent the polygon
	std::vector<b2Vec2> generateConvexPolygon(int sides, float size);

	// Check if a series of points forms a convex polygon
	// points - Points to check. This is in clockwise order
	// returns: If the series of points forms a valid convex polygon
	bool isValidConvexPolygon(const std::vector<b2Vec2>& points);

	// Calculate the angle between 3 verticies, ordered in v1, v2, v3
	// v1 - Vertex 1
	// v2 - Vertex 2
	// v3 - Vertex 3
	// returns: The angle between the 3 verticies measured in radians
	float getAngle(Vector2 v1, Vector2 v2, Vector2 v3);

	// Wrap a value inside a range
	// val - Value to wrap
	// min - Min value the value can be
	// max - Max value the value can be
	// returns: The value wrapped between the range defined by min and max
	int wrap(int val, int min, int max);

};

#endif
