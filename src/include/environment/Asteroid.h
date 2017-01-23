#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "Unit.h"

class Map;

class Asteroid : public Entity {
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
	
	// Events //////////////////////////////////////////////////////////////////
	
	// Occurs when an Asteroid dies
	void onDeath();

	// Movement methods ////////////////////////////////////////////////////////

	// Get the drift of this Asteroid
	// returns _drift
	inline const Vector2& getDrift() const { return _drift; }

	// Set the drift of this Asteroid
	// drift - New drift to set this Asteroid to. The drift is in units
	//		of the Map, not Box2D
	void setDrift(const Vector2& drift);

	// Set the drift of this Asteroid
	// x - X component of the drift to set in Map units
	// y - Y component of the drift to set in Map units
	inline void setDrift(float x, float y) { setDrift(Vector2(x, y)); }

	// Set the velocity of the Asteroid
	// x - X component of the velocity in Map units
	// y - Y component of the velocity in Map units
	virtual void setVelocity(float x, float y);

	// Update the position of this Object all all vars
	// x - X coord of the map to update to
	// y - Y coord of the map to update to
	void updatePosition(float x, float y);

	// Getters and setters /////////////////////////////////////////////////////

	// Get the max radius this Asteroid can have
	// returns: _maxRadius
	inline float getMaxRadius() const { return _maxRadius; }

	// Set the ObjectType of this Object
	// type - Type to set the ObjectType to
	virtual void setObjectType(int type);

protected:

	// How many pixels a second the Asteroid will drift from its current
	// position in Map units. If two Asteroid collide they will bounch off
	// each other and a new drift will be assigned
	Vector2 _drift;

	// Use a different shape when drawing an Asteroid, have sides and stuff
	sf::ConvexShape _conShape;

	float _maxRadius; // Max radius of this Asteroid

	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
