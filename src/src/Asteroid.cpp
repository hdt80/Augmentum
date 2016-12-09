#include "Asteroid.h"

#include "Map.h"
#include "Random.h"
#include "Convert.h"

// Use the built-in math definitions (M_PI)
#define _USE_MATH_DEFINES
#include <cmath>

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
	bdf.position.Set(x, y);
	bdf.angle = Random::randFloat(0, M_PI); // Radians

	_b2Box = map->getWorld()->CreateBody(&bdf);

	// Get the verticies that define this Asteroid
	std::vector<b2Vec2> points = getPoints(maxRadius);

	b2PolygonShape pShape;
	pShape.Set(&points[0], 8);

	b2FixtureDef fd; // Fixture def of the b2Body this Asteroid will use
	fd.shape = &pShape;
	fd.density = 1.0f;
	fd.friction = 0.8f;

	_b2Box->CreateFixture(&fd);
	_b2Box->SetLinearDamping(0.4f);

	// Set up the sf::Shape
	_conShape.setPointCount(8);
	for (unsigned int i = 0; i < points.size(); ++i) {
		_conShape.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	_conShape.setOutlineColor(sf::Color::Black);
	_conShape.setOutlineThickness(-3.0f);
	_conShape.setFillColor(sf::Color::Red);
	_conShape.setRotation(convert::toDeg(bdf.angle));
}

Asteroid::~Asteroid() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

const std::vector<b2Vec2> Asteroid::getPoints(float radius) {
	std::vector<b2Vec2> points(8);
	b2PolygonShape testShape; // Shape to test the points

	// Use a do while so the first iteration is completed
	do {
		// TODO: Make this not a regular polygon
		for (unsigned int i = 0; i < 8; ++i) {
			points[i] = 
				b2Vec2(radius * sin(M_PI / 4 * i), radius * cos(M_PI / 4 * i));
		}
		testShape.Set(&points[0], 8);
	} while (!testShape.Validate());

	return points;
}

void Asteroid::updatePosition(float x, float y) {
	_conShape.setPosition(x, y);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_conShape);
}
