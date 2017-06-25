#include "game/ContactListener.h"

#include "game/Object.h"
#include "game/BitWise.h"

#include "logger/Logger.h"

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
	AG_INFO("BeginContact", this);

	void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	Object* a = nullptr;
	Object* b = nullptr;

	if (userDataA) {
		a = static_cast<Object*>(userDataA);
	} else {
		AG_WARN("Fixture A has no userdata, %x", contact->GetFixtureA());
	}

	if (userDataB) {
		b = static_cast<Object*>(userDataB);
	} else {
		AG_WARN("Fixture B has no userdata, %x", contact->GetFixtureB());
	}

	if (a && b) {
		a->addCollision(b);
		b->addCollision(a);
	}
}

void ContactListener::EndContact(b2Contact* contact) {
	AG_INFO("EndContact", this);

	void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	Object* a = nullptr;
	Object* b = nullptr;

	if (userDataA) {
		a = static_cast<Object*>(userDataA);
	} else {
		AG_WARN("Fixture A has no userdata, %x", contact->GetFixtureA());
	}

	if (userDataB) {
		b = static_cast<Object*>(userDataB);
	} else {
		AG_WARN("Fixture B has no userdata, %x", contact->GetFixtureB());
	}

	if (a && b) {
		a->removeCollision(b);
		b->removeCollision(a);
	}
}

void ContactListener::PreSolve(b2Contact* contact,
		const b2Manifold* oldManifold) {
	AG_INFO("PreSolve", this);
}

void ContactListener::PostSolve(b2Contact* contact,
		const b2Manifold* newManifold) {
	AG_INFO("PostSolve", this);
}
