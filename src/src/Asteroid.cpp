#include "Asteroid.h"

#include "Map.h"

// Use the built-in math definitions (M_PI)
#define _USE_MATH_DEFINES
#include <cmath>

////////////////////////////////////////////////////////////////////////////////
// Asteroid ctor and dtor
////////////////////////////////////////////////////////////////////////////////

Asteroid::Asteroid(Map* map, float x, float y, float maxRadius)
	: Object(map, x, y, Stats(0.0f), maxRadius) {

	_b2Box = nullptr;

	b2BodyDef bdf;
	bdf.type = b2_dynamicBody;
	bdf.position.Set(x, y);
	bdf.angle = 0; // Radians
	_b2Box = map->getWorld()->CreateBody(&bdf);

	std::vector<b2Vec2> points = getPoints(maxRadius);

	b2PolygonShape pShape;
	pShape.Set(&points[0], 8);

	b2FixtureDef fd;
	fd.shape = &pShape;
	fd.density = 1.0f;
	fd.friction = 0.8f;
	_b2Box->CreateFixture(&fd);

	_b2Box->SetLinearDamping(0.4f);

	if (_b2Box) {
		_b2Box->SetUserData(this);
	}

	_conShape.setPointCount(8);

	// Set up the sf::Shape
	for (unsigned int i = 0; i < points.size(); ++i) {
		_conShape.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	_conShape.setOutlineColor(sf::Color::Black);
	_conShape.setOutlineThickness(-3.0f);
	_conShape.setFillColor(sf::Color::Red);
}

Asteroid::~Asteroid() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

const std::vector<b2Vec2> Asteroid::getPoints(float radius) {
	std::vector<b2Vec2> points(8);
	b2PolygonShape testShape; // Shape to test the points

	do {
		// TODO: Make this not a regular polygon
		for (unsigned int i = 0; i < 8; ++i) {
			points[i] = b2Vec2(x + radius * sin(45 * i),
				y + radius * cos(45 * i));
			CORE_INFO("[Asteroid %x] point %d (%g, %g)", this,
				i, points[i].x, points[i].y);
		}
		testShape.Set(&points[0], 8);
	} while (!testShape.Validate());

	return points;
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_conShape);
}
