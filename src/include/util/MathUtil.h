#ifndef _MATH_UTIL_H
#define _MATH_UTIL_H

#include <vector>

#include "Box2D/Box2D.h"

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
	// points - How many points/sides the polygon should have
	// size - How many units across the polygon should be
	// returns: A vector containing the points used to represent the polygon
	std::vector<b2Vec2> generatePolygon(int points, float size);

};

#endif
