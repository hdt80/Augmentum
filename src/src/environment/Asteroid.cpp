#include "environment/Asteroid.h"

#include "Map.h"
#include "util/Random.h"
#include "util/MathUtil.h"

////////////////////////////////////////////////////////////////////////////////
// Asteroid ctor and dtor
////////////////////////////////////////////////////////////////////////////////

Asteroid::Asteroid(Map* map, float x, float y, float maxRadius)
	: Object(map, x, y, Stats(0.0f), maxRadius) {

	if (_b2Box) {
		map->getWorld()->DestroyBody(_b2Box);
		_b2Box = nullptr;
	}

	b2BodyDef bdf;
	bdf.type = b2_staticBody;
	bdf.position.Set(MathUtil::toB2(x), MathUtil::toB2(y));
	bdf.angle = Random::randFloat(0, MathUtil::PI); // Radians

	_b2Box = map->getWorld()->CreateBody(&bdf);

	// Get the verticies that define this Asteroid
	std::vector<b2Vec2> points = MathUtil::generateConvexPolygon(8, maxRadius);

	// Vector that will hold all the points used to create the Box2D shape
	std::vector<b2Vec2> b2Points(points.size());

	for (unsigned int i = 0; i < points.size(); ++i) {
		// Scale all the points to the scale Box2D uses
		b2Points[i] =
			b2Vec2(MathUtil::toB2(points[i].x), MathUtil::toB2(points[i].y));
	}

	b2PolygonShape pShape;
	pShape.Set(&b2Points[0], points.size());

	b2FixtureDef fd; // Fixture def of the b2Body this Asteroid will use
	fd.shape = &pShape;
	fd.density = 1.0f;
	fd.friction = 0.4f;

	_b2Box->CreateFixture(&fd);
	_b2Box->SetLinearDamping(0.4f);

	// Set up the sf::Shape
	_conShape.setPointCount(points.size());
	for (unsigned int i = 0; i < points.size(); ++i) {
		_conShape.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	_conShape.setOutlineColor(sf::Color::Black);
	_conShape.setOutlineThickness(-3.0f);
	_conShape.setFillColor(sf::Color(96, 96, 96));
	_conShape.setRotation(MathUtil::radToDeg(bdf.angle));

	setObjectType(ObjectType::BOUNDARY);
}

Asteroid::~Asteroid() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void Asteroid::updatePosition(float x, float y) {
	_conShape.setPosition(x, y);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_conShape);
}

////////////////////////////////////////////////////////////////////////////////
// Events
////////////////////////////////////////////////////////////////////////////////

void Asteroid::onProjectileHit(Projectile* p) {
	CORE_INFO("[Asteroid %x] Hit", this);
}
