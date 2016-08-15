#include "Ship.h"
#include "bounds/RectangleBoundBox.h"

// =============================================================================
// Ctor and Dtor
// =============================================================================
//Ship::Ship()
//	: Ship(nullptr, 0.0f, 0.0f, Stats()) {
//
//}

//
Ship::Ship(Map* map, float x, float y, Stats s)
	: Ship(map, x, y, s, 30, sf::Color::Red) {
	
}

//
Ship::Ship(Map* map, float x, float y, Stats s,
		int sides, sf::Color color)
 	: Unit(map, x, y, s),
		_sides(sides), _color(color) {
	
	_shape.setRadius(20);
	_shape.setPointCount(sides);
	_shape.setFillColor(color);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(-3.0f);

	RectangleBoundBox* box =
		new RectangleBoundBox(Vector2(x, y), Vector2(20.0f, 20.0f));

	_boundBox = box;
}
