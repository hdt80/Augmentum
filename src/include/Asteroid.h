#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "Object.h"

class Map;

class Asteroid : public Object {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Asteroid ctor
	// map - Map this Asteroid exists on
	// x - X coord of the world to spawn the Asteroid on
	// y - Y coord of the world to spawn the Asteroid on
	// maxRadius - Max size this Asteroid can be
	Asteroid(Map* map, float x, float y, float maxRadius);

	// Asteroid dtor
	virtual ~Asteroid();

	// Methods /////////////////////////////////////////////////////////////////
protected:

	// Get the points that will make up this Asteroid
	// radius - Max radius of the shape
	// returns: A vector with each point
	const std::vector<b2Vec2> getPoints(float radius);

	// Use a different shape when drawing an Asteroid, have sides and stuff
	sf::ConvexShape _conShape;

	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
