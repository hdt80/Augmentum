#pragma once

namespace ag {

////////////////////////////////////////////////////////////////////////////////
// Utility template class for manipulating 3D vectors. A Vec3 is simply a 
// mathmatical vector with 3 components (x, y and z).
//
// The template parameter is for the kind of coodinates. It can be any type that
// supports arithmetic operations (+, -, *, /) and comparisions (==, !=), for
// example, ints or floats.
//
// Generally the templated form is not used, and the most common types (ints,
// floats and unsigned ints) have typedefs:
//		ag::Vec3i		ag::Vec3<int>
//		ag::Vec3f		ag::Vec3<float>
//		ag::Vec3u		ag::Vec3<unsigned int>
//
// For 2 dimensional vectors see ag::Vec2
////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Vec3 {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Nullary ctor. All the values will be initalized to zero
	//
	Vec3()
		: x(0), y(0), z(0) {}

	// Copy ctor
	//
	// v - Vec3 to copy
	//
	Vec3(const Vec3<T>& v)
		: x(v.x), y(v.y), z(v.z) {}

	// Coord ctor
	//
	// X - X component of the Vec3
	// Y - Y component of the Vec3
	// Z - Z component of the Vec3
	//
	Vec3(T X, T Y, T Z)
		: x(X), y(Y), z(Z) {}

	// Vars ////////////////////////////////////////////////////////////////////
	
	// Components of the Vec3. These are public as having to use getters and
	// setters would be useless
	//
	T x, y, z;
};

////////////////////////////////////////////////////////////////////////////////
// Vec3 operator overloads
////////////////////////////////////////////////////////////////////////////////

// Operator overload for negation. This will take the Vec3 provided and provide
//		the Vec3 opposite of it
//
// vec - Vec3 to be negated
//
// returns: Memberwise negatation of the Vec3
//
template <typename T>
Vec3<T> operator -(const Vec3<T>& vec) {
	return Vec3<T>(-vec.x, -vec.y, -vec.z);
}

// Operator overload for addition. This will return the value of the x, y and z
//		components added
//
// left - Left operand
// right - Right operand
//
// returns: Memberwise addition of the Vec3's components
//
template <typename T>
Vec3<T> operator +(const Vec3<T>& left, const Vec3<T>& right) {
	return Vec3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

// Operator overload for addition. This will return a reference to left, which
//		was added to right
//
// left - Left operand, the Vec3 to be added to
// right - Right operand, the Vec3 being added to left
//
// returns: A reference to left
//
template <typename T>
Vec3<T>& operator +=(Vec3<T>& left, const Vec3<T>& right) {
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;

	return left;
}

// Operator overload for subtraction. This will return the value of the x, y and
//		z components subtracted
//
// left - Left operand
// right - Right operand
//
// returns: Memberwise subtraction of the Vec3's components
//
template <typename T>
Vec3<T> operator -(const Vec3<T>& left, const Vec3<T>& right) {
	return Vec3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

// Operator overload for subtraction. This will return a reference to left,
//		which was subtracted from right
//
// left - Left operand, the Vec3 being subtracted from
// right - Right operand, the Vec3 to be used for subtraction
//
// returns: A reference to left
//
template <typename T>
Vec3<T>& operator -=(Vec3<T>& left, const Vec3<T>& right) {
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;

	return left;
}

// Operator overload for scalar multiplication
//
// vec - Vec3 whose components will be multiplied by the scalar
// scalar - Scalar to multiple the components of left by
//
// returns: A Vec3 containing the components of vec multiplied by scalar
//
template <typename T>
Vec3<T> operator *(const Vec3<T>& vec, T scalar) {
	return Vec3<T>(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

// Operator overload for scalar multiplication. This will take the vec's
//		components and multiply each one by the scalar
//
// vec - Vec3 to be multiplied by scalar
// scalar - Scalar value to multiply vec by
//
// returns: A reference to vec
//
template <typename T>
Vec3<T>& operator *=(Vec3<T>& vec, T scalar) {
	vec.x *= scalar;
	vec.y *= scalar;
	vec.z *= scalar;

	return vec;
}

// Operator overload for division. This will take left and divide each component
//		by scalar and return a new Vec3 with those values
//
// left - Left operand
// scalar - Scalar to divide left by
//
// returns: A Vec3 with each of left's components divided by scalar
//
template <typename T>
Vec3<T> operator /(const Vec3<T>& left, T scalar) {
	return Vec3<T>(left.x / scalar, left.y / scalar, left.z / scalar);
}

// Operator overload for division. This will take the components of left and
//		divide each one by scalar
//
// left - Left operand (Vec3 to be divided)
// scalar - Scalar divisor
//
// returns: A reference to left
//
template <typename T>
Vec3<T>& operator /=(Vec3<T>& left, T scalar) {
	left.x /= scalar;
	left.y /= scalar;
	left.z /= scalar;

	return left;
}

// Operator overload for equality
//
// left - Left operand
// right - Right operand
//
// returns: If all the components of Vec3 are equal
//
template <typename T>
bool operator ==(const Vec3<T>& left, const Vec3<T>& right) {
	return left.x == right.x
		&& left.y == right.y
		&& left.z == right.z;
}

// Operator overload for inequality
//
// left - Left operand
// right - Right operand
//
// returns: If left and right are unequal
//
template <typename T>
bool operator !=(const Vec3<T>& left, const Vec3<T>& right) {
	return !(left == right);
}

typedef Vec3<int>			Vec3i;
typedef Vec3<float>			Vec3f;
typedef Vec3<unsigned int>	Vec3u;

} // namespace ag
