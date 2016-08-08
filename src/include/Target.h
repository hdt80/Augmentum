#ifndef _TARGET_H
#define _TARGET_H

#include "Vector2.h"

class Target {
public:
	Target(float x, float y) : x(x), y(y) {}
	Target(Vector2 v) : x(v.X), y(v.Y) {}
	Target(Vector2* v) : x(v->X), y(v->Y) {}
	virtual ~Target(){}

	float distanceWith(float dx, float dy);
	float distanceWith(Target* t);
	float distanceWithSqr(float dx, float dy);
	float distanceWithSqr(Target* t);

	Vector2 getPosition() { return Vector2(x, y); }
	float getX() const { return x; }
	float getY() const { return y; }

	virtual void setPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}

	virtual bool isSimpleTarget() { return true; }
protected:
	float x;
	float y;
};

#endif
