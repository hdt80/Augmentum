#include "game/Vector2.h"

#include <math.h>

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

float Vector2::length() const {
	return sqrt(X * X + Y * Y);
}

float Vector2::sqrtLength() const {
	return (X * X + Y * Y);
}

Vector2 Vector2::normalize() const {
	Vector2 v;
	float length = this->length();

	if (length != 0) {
		v.X = X / length;
		v.Y = Y / length;
	}
	return v;
}

float Vector2::angle() const {
	return std::atan2(Y, X);
}
