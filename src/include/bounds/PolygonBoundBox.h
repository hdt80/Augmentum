#ifndef _POLYGON_BOUND_BOX
#define _POLYGON_BOUND_BOX

#include "BoundBox.h"

class PolygonBoundBox : public BoundBox {
public:
	PolygonBoundBox();
	PolygonBoundBox(Vector2 origin, int pointCount);

	bool contains(float x, float y);

protected:
	int _pointCount;
};

#endif
