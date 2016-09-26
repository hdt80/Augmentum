#include "ContactListener.h"
#include "Logger.h"

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
	CORE_INFO("[ContactListener %x] BeginContact", this);
}

void ContactListener::EndContact(b2Contact* contact) {
	CORE_INFO("[ContactListener %x] EndContact", this);
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	CORE_INFO("[ContactListener %x] PreSolve", this);
}

void ContactListener::PostSolve(b2Contact* contact, const b2Manifold* newManifold) {
	CORE_INFO("[ContactListener %x] PostSolve", this);
}
