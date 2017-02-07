#ifndef VECTOR2_H
#define	VECTOR2_H

class Vector2 {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	Vector2() : Vector2(0, 0) {}
	Vector2(float X, float Y) : X(X), Y(Y) {}
	Vector2(const Vector2& v) : X(v.X), Y(v.Y) {}
	~Vector2() {};

	// Methods /////////////////////////////////////////////////////////////////

	// Get the Euclidean distance of this Vector
	// returns: Euclidean distance of this Vector
	float length() const;

	// Get the Euclidean distance squared of this Vector
	// returns: Euclidean distance of this Vector squared
	float sqrtLength() const;

	// Turn this Vector into an angle
	// returns: Angle of the Vector in degrees
	float angle() const;

	// Normalize the Vector
	// returns: This Vector normalized
	Vector2 normalize() const;

	float X, Y; // Coords of this Vector

	// Operator overloads //////////////////////////////////////////////////////

	void operator= (const Vector2& a_V) {
		X = a_V.X;
		Y = a_V.Y;
	}

	void operator += (const Vector2& a_V) {
		X += a_V.X;
		Y += a_V.Y;
	}

	void operator += (Vector2* a_V) {
		X += a_V->X;
		Y += a_V->Y;
	}

	void operator -= (const Vector2& a_V) {
		X -= a_V.X;
		Y -= a_V.Y;
	}

	void operator -= (Vector2* a_V) {
		X -= a_V->X;
		Y -= a_V->Y;
	}
	
	void operator *= (const float f) {
		X *= f;
		Y *= f;
	}

	void operator *= (const Vector2& a_V) {
		X *= a_V.X;
		Y *= a_V.Y;
	}

	void operator *= (Vector2* a_V) {
		X *= a_V->X;
		Y *= a_V->Y;
	}

	Vector2 operator- () const {
		return Vector2(-X, -Y);
	}

	friend Vector2 operator + (const Vector2& v1, const Vector2& v2) {
		return Vector2(v1.X + v2.X, v1.Y + v2.Y);
	}

	friend Vector2 operator + (const Vector2& v1, Vector2* v2) {
		return Vector2(v1.X + v2->X, v1.Y + v2->Y);
	}

	friend Vector2 operator - (const Vector2& v1, const Vector2& v2) {
		return Vector2(v1.X - v2.X, v1.Y - v2.Y);
	}

	friend Vector2 operator - (const Vector2& v1, Vector2* v2) {
		return Vector2(v1.X - v2->X, v1.Y - v2->Y);
	}

	friend Vector2 operator - (const Vector2* v1, Vector2& v2) {
		return Vector2(v1->X - v2.X, v1->Y - v2.Y);
	}

	friend Vector2 operator * (const Vector2& v, const float f) {
		return Vector2(v.X * f, v.Y * f);
	}

	friend Vector2 operator * (const Vector2& v1, const Vector2& v2) {
		return Vector2(v1.X * v2.X, v1.Y * v2.Y);
	}

	friend Vector2 operator * (const float f, const Vector2& v) {
		return Vector2(v.X * f, v.Y * f);
	}

	friend Vector2 operator / (const Vector2& v, const float f) {
		return Vector2(v.X / f, v.Y / f);
	}

	friend Vector2 operator / (const Vector2& v1, const Vector2& v2) {
		return Vector2(v1.X / v2.X, v1.Y / v2.Y);
	}

	friend Vector2 operator / (const float f, const Vector2& v) {
		return Vector2(v.X / f, v.Y / f);
	}
};

#endif
