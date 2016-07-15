#include "Vector2.h"
#include <math.h>

float Vector2::length() {
	return sqrt(X * X + Y * Y);
}

float Vector2::sqrtLength() {
	return (X * X + Y * Y);
}

Vector2 Vector2::normalize() {
	Vector2 v;
	float length = this->length();

	if (length != 0) {
		v.X = X / length;
		v.Y = Y / length;
	}
	return v;
}