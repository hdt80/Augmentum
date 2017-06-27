#include "game/environment/Asteroid.h"

#include "game/Map.h"
#include "game/GameWindow.h"
#include "game/Databases.h"

#include "util/UtilRandom.h"
#include "util/UtilMath.h"
#include "util/Vec2.h"

////////////////////////////////////////////////////////////////////////////////
// Asteroid ctor and dtor
////////////////////////////////////////////////////////////////////////////////

Asteroid::Asteroid(Map* map, float x, float y, float maxRadius)
	: Entity(map, x, y, maxRadius, 200),
		_maxRadius(maxRadius) {

	setMaxHealth(200);
	setHealth(getMaxHealth());

	if (maxRadius < 0) {
		AG_WARN("Cannot have a maxRadius of < 0 (%g)", _maxRadius);
	}

	// If there's a body it probably isn't a proper Asteroid one
	if (_b2Box) {
		map->getWorld()->DestroyBody(_b2Box);
		_b2Box = nullptr;
	}

	b2BodyDef bdf;
	bdf.type = b2_dynamicBody;
	bdf.position.Set(ag::Math::toB2(x), ag::Math::toB2(y));
	bdf.angle = ag::Random::randFloat(0, ag::Math::PI); // Radians

	_b2Box = map->getWorld()->CreateBody(&bdf);

	// Get the verticies that define this Asteroid
	std::vector<ag::Vec2f> points =
		ag::Math::generateConvexPolygon(8, maxRadius);

	// Because I request an 8 sides convex polygon, but I'm not guaranteed to
	// get one I use points.size() to determine the size of the rest of the
	// objects used in creation

	// Vector that will hold all the points used to create the Box2D shape
	std::vector<b2Vec2> b2Points(points.size());
	for (unsigned int i = 0; i < points.size(); ++i) {
		// Scale all the points to the scale Box2D uses
		b2Points[i] =
			b2Vec2(ag::Math::toB2(points[i].x), ag::Math::toB2(points[i].y));
	}

	b2PolygonShape pShape;
	pShape.Set(&b2Points[0], points.size());

	b2FixtureDef fd; // Fixture def of the b2Body this Asteroid will use
	fd.shape = &pShape;
	fd.density = 10.0f; // Make this really heavy
	fd.restitution = 1.0f;

	_b2Box->CreateFixture(&fd);

	// Set up the sf::Shape
	_conShape.setPointCount(points.size());
	for (unsigned int i = 0; i < points.size(); ++i) {
		_conShape.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	_conShape.setOutlineColor(sf::Color::Black);
	_conShape.setOutlineThickness(-3.0f);
	_conShape.setFillColor(sf::Color(96, 96, 96));
	_conShape.setRotation(ag::Math::radToDeg(bdf.angle));

	setObjectType(ObjectType::BOUNDARY);

	_b2Box->SetUserData(this);

	updatePosition(getX(), getY());
}

Asteroid::~Asteroid() {
	// Deleting a Box2D body by calling the dtor will break a lot of things
	if (_b2Box) {
		_map->getWorld()->DestroyBody(_b2Box);
		_b2Box = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Asteroid::updatePosition(float x, float y) {
	_conShape.setPosition(x, y);
}

void Asteroid::setVelocity(float x, float y) {
	// Don't bother accelerating to the velocity
	_b2Box->SetLinearVelocity(b2Vec2(ag::Math::toB2(x), ag::Math::toB2(y)));
}

void Asteroid::setDrift(const Vector2& drift) {
	_drift = drift;
	setVelocity(drift.X, drift.Y);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_conShape);
}

void Asteroid::setObjectType(int type) {
	_objType = type;

	if (!_b2Box) {
		return;
	}

	int allTypes = std::pow((double) 2, ObjectType::COUNT) - 1;

	for (b2Fixture* fix = _b2Box->GetFixtureList(); fix; fix = fix->GetNext()) {
		b2Filter filt = fix->GetFilterData();

		// Category bits - What I am
		filt.categoryBits = type;
		// Mask bits - What the Object collides with. Asteroid collide with
		// everything, including other asteroids
		filt.maskBits = allTypes;

		fix->SetFilterData(filt);
	}
}

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////

void Asteroid::onDeath() {
	Object::onDeath();

	GameWindow::Emitter.emit(
		&Databases::ParticleDefs.get("asteroid_death"),
		getX(), getY(), 100, -1);
}
