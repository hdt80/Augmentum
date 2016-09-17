#include "bounds/PolygonBoundBox.h"

PolygonBoundBox::PolygonBoundBox() {

}

PolygonBoundBox::PolygonBoundBox(Vector2 origin, int pointCount) {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

// https://stackoverflow.com/questions/217578
bool PolygonBoundBox::contains(float x, float y) {
	unsigned int i, j;
	bool c = false;
	for (i = 0, j = getPointCount() - 1; i < getPointCount(); j = i++) {
		if (((getPoint(i).Y > y) != (getPoint(j).Y > y)) &&
			(x < (getPoint(j).X - getPoint(i).X) * (y - getPoint(i).Y)
			 / (getPoint(j).Y - getPoint(i).Y) + getPoint(i).X)) {
				c = !c;
		}
	}
	return c;
}
