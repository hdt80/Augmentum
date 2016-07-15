#ifndef _PATH_H
#define _PATH_H

#include <vector>
#include "Vector2.h"

class Path {
public:
	Path();
	~Path();

	void addPoint(float x, float y);

	Vector2* getPoint(unsigned int index);

	unsigned int size() { return points.size(); }
	std::vector<Vector2*> data() { return points; }

protected:
	std::vector<Vector2*> points;
};

#endif