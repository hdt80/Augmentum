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
	CORE_INFO("[Object %x] BeginContact", this);
}

void ContactListener::EndContact(b2Contact* contact) {
	CORE_INFO("[Object %x] EndContact", this);
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	CORE_INFO("[Object %x] PreSolve", this);
}

void ContactListener::PostSolve(b2Contact* contact, const b2Manifold* newManifold) {
	CORE_INFO("[Object %x] PostSolve", this);
}
