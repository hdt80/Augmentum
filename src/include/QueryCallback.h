#ifndef _QUERY_CALLBACK_H
#define _QUERY_CALLBACK_H

#include "Box2D/Box2D.h"
#include "Object.h"

#include <vector>

class QueryCallback : public b2QueryCallback {
public:

	// Public vars /////////////////////////////////////////////////////////////
	
	// All the bodies found in the AABB query
	std::vector<b2Body*> bodiesIn;

	// Methods /////////////////////////////////////////////////////////////////

	// Inherited from b2QueryCallback
	bool ReportFixture(b2Fixture* fixture);

	// Static methods //////////////////////////////////////////////////////////
	
	// Get all the Objects inside an area
	// world - b2World to query
	// x - X coord of the world
	// y - Y coord of the world
	// radius - Radius around the point (x, y)
	static std::vector<Object*> getObjects(b2World* world,
		float x, float y, float radius);

protected:
};

#endif
