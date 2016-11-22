#include "ContactListener.h"
#include "Logger.h"

#include "Object.h"
#include "BitWise.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and Dtor
////////////////////////////////////////////////////////////////////////////////
ContactListener::ContactListener(b2World* world) {
	world->SetContactListener(this);
}

ContactListener::~ContactListener() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////
void ContactListener::BeginContact(b2Contact* contact) {
	CORE_INFO("BeginContact", this);

	void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	Object* a = nullptr;
	Object* b = nullptr;

	if (userDataA) {
		a = static_cast<Object*>(userDataA);
	}

	if (userDataB) {
		b = static_cast<Object*>(userDataB);
	}

	if (a && b) {
		a->addCollision(b);
		b->addCollision(a);
	}
}

void ContactListener::EndContact(b2Contact* contact) {
	CORE_INFO("EndContact", this);

	void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	Object* a = nullptr;
	Object* b = nullptr;

	if (userDataA) {
		a = static_cast<Object*>(userDataA);
	}

	if (userDataB) {
		b = static_cast<Object*>(userDataB);
	}

	if (a && b) {
		a->removeCollision(b);
		b->removeCollision(a);
	}
}

void ContactListener::PreSolve(b2Contact* contact,
		const b2Manifold* oldManifold) {
	CORE_INFO("PreSolve", this);
}

void ContactListener::PostSolve(b2Contact* contact,
		const b2Manifold* newManifold) {
	CORE_INFO("PostSolve", this);
}
