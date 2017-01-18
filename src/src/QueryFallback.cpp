#include "QueryCallback.h"

#include "util/ObjectUtil.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

bool QueryCallback::ReportFixture(b2Fixture* fixture) {
	bodiesIn.push_back(fixture->GetBody());
	return true; // Keep going till all the fixtures in the AABB area are found
}

////////////////////////////////////////////////////////////////////////////////
// Static methods
////////////////////////////////////////////////////////////////////////////////

std::vector<Object*> QueryCallback::getObjects(b2World* world,
		float x, float y, float r) {

	QueryCallback qback;
	b2AABB aabb;
	aabb.upperBound = b2Vec2(x + r, y + r);
	aabb.lowerBound = b2Vec2(x - r, y - r);

	world->QueryAABB(&qback, aabb);

	std::vector<Object*> objs;
	objs.resize(qback.bodiesIn.size());

	Object* iter = nullptr;
	for (unsigned int i = 0; i < qback.bodiesIn.size(); ++i) {
		if ((iter = ObjectUtil::toObject(qback.bodiesIn[i]->GetUserData()))) {
			objs[i] = iter;
		} else {
			CORE_WARN("Failed to cast %x to an Object*", iter);
		}
	}

	return objs;
}
