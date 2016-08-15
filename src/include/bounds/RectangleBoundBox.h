#ifndef _RECTANGLE_BOUND_BOX_H
#define _RECTANGLE_BOUND_BOX_H

#include "BoundBox.h"

class RectangleBoundBox : public BoundBox {
public:
	RectangleBoundBox();
	RectangleBoundBox(Vector2 origin, Vector2 dims);
	
	virtual bool contains(float x, float y);

protected:
	Vector2 _dimensions;
};

#endif
