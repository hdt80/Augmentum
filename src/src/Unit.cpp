#include "Unit.h"
#include "Map.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor and deconstructor
///////////////////////////////////////////////////////////////////////////////
Unit::Unit() {
	
}

Unit::Unit(Map* map, float x, float y, Stats s, int sides, sf::Color c)
	: Object(map, x, y, s) {

	_shape.setRadius(20);
	_shape.setPointCount(sides);
	_shape.setFillColor(c);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(-3.0f);

	_b2Box = nullptr;

	b2BodyDef bdf;
	bdf.type = b2_dynamicBody;
	bdf.position.Set(x, y);
	bdf.angle = 0; // Radians
	_b2Box = map->getWorld()->CreateBody(&bdf);

	b2CircleShape cs;
	cs.m_p.Set(0, 0);
	cs.m_radius = 20;

	b2PolygonShape dBox;
	dBox.SetAsBox(10.0f, 10.0f);

	b2FixtureDef fd;
	//fd.shape = &cs;
	fd.shape = &dBox;
	fd.density = 1.0f;
	fd.friction = 0.4f;
	_b2Box->CreateFixture(&fd);
}

Unit::~Unit() {}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////
void Unit::draw(sf::RenderTarget& target, sf::RenderStates stats) const {
	target.draw(_shape);
}
