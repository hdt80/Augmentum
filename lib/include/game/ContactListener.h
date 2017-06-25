#pragma once

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener {
public:

	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// ContactListener ctor
	// world - World this ContactListener will listen to
	ContactListener(b2World* world);

	// ContactListener dtor
	~ContactListener();

	// Methods inherited from b2ContactListener
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2Manifold* newManifold);

private:
};
