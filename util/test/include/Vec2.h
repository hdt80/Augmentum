#pragma once

namespace ag {

////////////////////////////////////////////////////////////////////////////////
// Utility template class for manipulating 2D vectors. A Vec2 is simply a
// mathmatical vector with 2 components (x and y)
//
// The template parameter is for the kind of coodinates. It can be any type that
// supports arithmetic operations (+, -, *, /) and comparisions (==, !=), for
// example, ints or floats.
//
// Generally the templated form is not used, and the most common types (ints,
// floats and unsigned ints) have typedefs:
//		ag::Vec2i		ag::Vec2<int>
//		ag::Vec2f		ag::Vec2<float>
//		ag::Vec2u		ag::Vec2<unsigned int>
//
// For 3 dimensional vectors see ag::Vec3
////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Vec2 {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Nullary ctor. All the values will be initalized to zero
	//
	Vec2()
		: x(0), y(0) {}

	// Copy ctor
	//
	// v - Vec2 to copy
	//
	Vec2(const Vec2<T>& v)
		: x(v.x), y(v.y) {}

	// Coord ctor
	//
	// X - X component of the Vec2
	// Y - Y component of the Vec2
	//
	Vec2(T X, T Y)
		: x(X), y(Y) {}

	// Vars ////////////////////////////////////////////////////////////////////
	
	// Components of the Vec2. These are public as having to use getters and
	// setters would be useless
	//
	T x, y;
};

////////////////////////////////////////////////////////////////////////////////
// Vec2 operator overloads
////////////////////////////////////////////////////////////////////////////////

// Operator overload for negation. This will take the Vec2 provided and provide
//		the Vec2 opposite of it
//
// vec - Vec2 to be negated
//
// returns: Memberwise negatation of the Vec2
//
template <typename T>
Vec2<T> operator -(const Vec2<T>& vec) {
	return Vec2<T>(-vec.x, -vec.y);
}

// Operator overload for addition. This will return the value of the x and y
//		components added
//
// left - Left operand
// right - Right operand
//
// returns: Memberwise addition of the Vec2's components
//
template <typename T>
Vec2<T> operator +(const Vec2<T>& left, const Vec2<T>& right) {
	return Vec2<T>(left.x + right.x, left.y + right.y);
}

// Operator overload for addition. This will return a reference to left, which
//		was added to right
//
// left - Left operand, the Vec2 to be added to
// right - Right operand, the Vec2 being added to left
//
// returns: A reference to left
//
template <typename T>
Vec2<T>& operator +=(Vec2<T>& left, const Vec2<T>& right) {
	left.x += right.x;
	left.y += right.y;

	return left;
}

// Operator overload for subtraction. This will return the value of the x and y
//		components subtracted
//
// left - Left operand
// right - Right operand
//
// returns: Memberwise subtraction of the Vec2's components
//
template <typename T>
Vec2<T> operator -(const Vec2<T>& left, const Vec2<T>& right) {
	return Vec2<T>(left.x - right.x, left.y - right.y);
}

// Operator overload for subtraction. This will return a reference to left,
//		which was subtracted from right
//
// left - Left operand, the Vec2 being subtracted from
// right - Right operand, the Vec2 to be used for subtraction
//
// returns: A reference to left
//
template <typename T>
Vec2<T>& operator -=(Vec2<T>& left, const Vec2<T>& right) {
	left.x -= right.x;
	left.y -= right.y;

	return left;
}

// Operator overload for scalar multiplication
//
// vec - Vec2 whose components will be multiplied by the scalar
// scalar - Scalar to multiple the components of left by
//
// returns: A Vec2 containing the components of vec multiplied by scalar
//
template <typename T>
Vec2<T> operator *(const Vec2<T>& vec, T scalar) {
	return Vec2<T>(vec.x * scalar, vec.y * scalar);
}

// Operator overload for scalar multiplication. This will take the vec's
//		components and multiply each one by the scalar
//
// vec - Vec2 to be multiplied by scalar
// scalar - Scalar value to multiply vec by
//
// returns: A reference to vec
//
template <typename T>
Vec2<T>& operator *=(Vec2<T>& vec, T scalar) {
	vec.x *= scalar;
	vec.y *= scalar;

	return vec;
}

// Operator overload for division. This will take left and divide each component
//		by scalar and return a new Vec2 with those values
//
// left - Left operand
// scalar - Scalar to divide left by
//
// returns: A Vec2 with each of left's components divided by scalar
//
template <typename T>
Vec2<T> operator /(const Vec2<T>& left, T scalar) {
	return Vec2<T>(left.x / scalar, left.y / scalar);
}

// Operator overload for division. This will take the components of left and
//		divide each one by scalar
//
// left - Left operand (Vec2 to be divided)
// scalar - Scalar divisor
//
// returns: A reference to left
//
template <typename T>
Vec2<T>& operator /=(Vec2<T>& left, T scalar) {
	left.x /= scalar;
	left.y /= scalar;

	return left;
}

// Operator overload for equality
//
// left - Left operand
// right - Right operand
//
// returns: If all the components of Vec2 are equal
//
template <typename T>
bool operator ==(const Vec2<T>& left, const Vec2<T>& right) {
	return left.x == right.x
		&& left.y == right.y;
}

// Operator overload for inequality
//
// left - Left operand
// right - Right operand
//
// returns: If left and right are unequal
//
template <typename T>
bool operator !=(const Vec2<T>& left, const Vec2<T>& right) {
	return !(left == right);
}

////////////////////////////////////////////////////////////////////////////////
// Typedefs for common types
////////////////////////////////////////////////////////////////////////////////

typedef Vec2<int>			Vec2i;
typedef Vec2<float>			Vec2f;
typedef Vec2<unsigned int>	Vec2u;

} // namespace ag
