#pragma once

#include "util/Vec2.h"

#include <vector>
#include <cmath>

namespace ag {

namespace Math {

////////////////////////////////////////////////////////////////////////////////
// Constant defines
////////////////////////////////////////////////////////////////////////////////

// PI
const float PI = 3.14159265358979323846f;

// Scale used between pixels and Box2D
const float B2BOX_SCALE = 30.f;

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

// Convert radians to degrees
//
// rad - Angle in radians
//
// returns: The equivalent angle in degrees
//
inline float radToDeg(float rad) { return rad * 57.295779f; }

// Convert degrees to radians
//
// deg - Angle in degrees
//
// returns: The equivalent angle in radians
//
inline float degToRad(float deg) { return deg * 0.0174532f; }

// Convert to Box2D's scale
//
// f - Value to convert
//
// returns: f in terms of Box2D's units
//
inline float toB2(float f) { return f / B2BOX_SCALE; }

// Convert from Box2D's scale
//
// f - Value to convert
//
// returns: f in terms of the units the game uses
//
inline float fromB2(float f) { return f * B2BOX_SCALE; }

// Generate a regular polygon
//
// sides - Number of the sides the polygon will have. The value must be greater
//		than 2, as a line isn't a polygon
// size - Scale of the generated polygon
//
// returns: A vector containing the points used to represent a regular polygon.
//		The points are defined in a clockwise fashion
//
std::vector<Vec2f> generatePolygon(int sides, float size);

// Generate a random non-regular polygon
//
// sides - Number of sides the polygon will have. The value must be greater
//		than 2, as a line isn't a polygon, and should be greater than 3, as all
//		triangles are regular and cannot be convex
// size - Scale of the regnerated polygon
//
// returns: A vector containing the points used to represent a convex polygon.
//		The points are defined in a clockwise fashion
//
std::vector<Vec2f> generateConvexPolygon(int sides, float size);

// Check if a series of points defined in a clockwise fashion form a convex
//		polygon
//
// points - Points used to represent the checked polygon. The points must be
//		defined in a clockwise fashion
//
// returns: If the points make a convex polygon
//
bool isValidConvexPolygon(const std::vector<Vec2f>& points);

// Wrap a value inside a range
//
// val - Value to be wrapped
// min - Minumum value allowed
// max - Maximum value allowed
//
// returns: val wrapped in the range of [min, max]
//
int wrap(int val, int min, int max);

// Linerally interpolate to a maximum value of a period of time
//
// max - Maximum value to interpolate to
// cur - Current value that is being interpolated
// dt - Deltatime, how much to interpolate
//
// returns: cur interpolated to the max value of the period of time dt
//
float approach(float max, float cur, float dt);

// Get the angle created by three points, which are represented by an ag::Vec.
//		The points are defined in the order they are defined
//
// v1 - First point
// v2 - Second point
// v3 - Third point
//
// returns: The angle formed by the three ag::Vecs in radians
//
float getAngle(const Vec2f& v1, const Vec2f& v2, const Vec2f& v3);

}; // namespace ag::Math

}; // namespace ag
