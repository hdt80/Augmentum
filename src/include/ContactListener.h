#ifndef _CONTACT_LISTENER_H
#define _CONTACT_LISTENER_H

#include <box2d/Box2d.h>

class ContactListener : public b2ContactListener {
public:
	ContactListener(b2World* world);
	~ContactListener();

	// Methods inherited from b2ContactListener
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2Manifold* newManifold);

private:
	ContactListener() {}
};

#endif
