#pragma once

#include "game/Scriptable.h"
#include "game/Target.h"

#include "lua/LuaScript.h"

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class Map;
class Perk;
class Projectile;

enum ObjectType {
	DEFAULT		= 0x0001,
	BOUNDARY	= 0x0002,
	FRIENDLY	= 0x0004,
	ENEMY		= 0x0008,
	PROJECTILE  = 0x0020,

	COUNT		= 0x0005 // How many types there are
};

// An Object is anything that exists in the Map. Objects are typically not
// interacted with, but can stil interact with other things on the Map
// Examples: Projectiles
class Object : public Scriptable, public Target,
	public sf::Drawable, public sf::Transformable {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////

	// Object ctor
	//
	// map - Map this Object is on
	// x - X position of the map to create the Object at
	// y - Y position of the map to create the Object at
	// size - Diameter of the Object
	//
	Object(Map* map, float x, float y, int size);

	// Object dtor
	//
	virtual ~Object();

	// Methods /////////////////////////////////////////////////////////////////

	// Load the Lua file and define all helper Lua methods
	//
	virtual void loadLua();

	// Events //////////////////////////////////////////////////////////////////
	
	// Occurs when this Object collides with another
	//
	// o - Object this Object collided with
	//
	virtual void onCollision(Object* o);

	// Occurs when this Object collides with a Projectile
	//
	// p - Projectile that his this Object
	//
	virtual void onProjectileHit(Projectile* p);

	// Occurs every update
	//
	// diff - Microseconds that happened for the update
	//
	virtual void onUpdate(int diff);

	// Occurs when this Object moves
	//
	// diff - Microseconds that happened for the move
	//
	virtual void onMove(int diff);

	// Update methods //////////////////////////////////////////////////////////

	// Moves the object depending on it's target, updating it's position
	//
	// diff - Milliseconds the object is supposed to move for
	//
	virtual void move(int diff);

	// Update the enemy depending on its target, updating its coords
	//
	// diff - Milliseconds since last update call
	//
	virtual void update(int diff);

	// Object type methods /////////////////////////////////////////////////////
	
	// Get what type of Object this is
	//
	// returns: Enum of _objType
	//
	inline int getObjectType() const { return _objType; }

	// Set the ObjectType of this Object
	//
	// type - Type to set the ObjectType to
	//
	virtual void setObjectType(int type);

	// Add an object type option to the _objType flag
	//
	// type - Object type option to set
	//
	void addObjectTypeOption(int type);

	// Query if this Object has a specific option set
	//
	// type - Type to check for
	//
	// returns: If _objType contains the flag
	//
	bool isObjectTypeOptionSet(int type);

	// Movement methods ////////////////////////////////////////////////////////
	
	// Set the velocity of this Object. The velocity won't be instantly set
	//		to this values, but accelerated to the vales
	//
	// x - X velocity to accelerate to
	// y - Y velcotiy to accelerate to
	//
	void setVelocity(float x, float y);

	// Update the position of this Object all all vars
	//
	// x - X coord of the map to update to
	// y - Y coord of the map to update to
	//
	virtual void updatePosition(float x, float y);

	// Get the current linear velocity
	//
	// returns: A Vector2 of the current linear velocity of this Object
	//
	Vector2 getVelocity() const;

	// Set the position of the Object
	//
	// pos - New position of the Object
	//
	inline virtual void setPosition(const Vector2& pos) {
		setPosition(pos.X, pos.Y); }

	// Set the position of the Object
	//
	// x - X coord of the map to set the position to
	// y - Y coord of the map to set the position to
	//
	virtual void setPosition(float x, float y);

	// Get the world position of this Object
	//
	// returns: the X coord of the world position
	//
	virtual float getX() const;

	// Get the world position of this Object
	//
	// returns: the Y coord of the world position
	//
	virtual float getY() const;

	// Get the diameter of thie Object
	//
	// returns: _size
	//
	inline virtual float getSize() const { return _size; }

	// Collision methods ///////////////////////////////////////////////////////
	
	// Add a new Object to the collision
	//
	// o - Object to add
	//
	void addCollision(Object* o);

	// Remove an Object from the collisions
	//
	// o - Object to remove
	//
	void removeCollision(Object* o);

	// See if an Object is collided with an Object
	//
	// o - Object to check for
	//
	// returns: If o is found in _collisions
	//
	bool hasCollision(Object* o) const;

	// If that point is within our collision box
	//
	// x - X coord of the map to check
	// y - Y coord of the map to check
	//
	// returns: If the point (x, y) is within the boundbox of this Object
	//
	bool contains(float x, float y) const;

	// If Object* o collides with us
	//
	// o - The Object to check collisions with
	//
	// returns: If the Object o colldes with this Object
	//
	bool collidesWith(Object* o) const;

	// Other getters ///////////////////////////////////////////////////////////
	
	// Get the Map this Object is on
	//
	// returns: Pointer to the Map this Object is on
	//
	inline Map* getMap() const { return _map; }

	// Get if this Object is to be removed in the next update of the Map
	//
	// return: _toRemove
	//
	inline bool isToRemove() const { return _toRemove; }

	// A simple target is just an (x, y) coord point. Because an Object
	//		isn't just a coord point it isn't a simple target
	//
	// returns: False
	//
	virtual bool isSimpleTarget() const { return false; }

	// Other setters ///////////////////////////////////////////////////////////
	
	// Set if this Object will be removed in the next update
	//
	// b - If the Object will be removed in the next update
	//
	inline void setToRemove(bool b) { _toRemove = b; }

protected:
	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	// All the Objects that are currently touching this Object
	std::vector<Object*> _collisions;

	sf::CircleShape _shape; // Shape to draw the Object with
	b2Body* _b2Box; // Collision box used in Box2D
	float _size; // Diameter of the Object

	Map* _map; // Map this object is located on

	LuaScript _lua; // Script associated with this Object

	int _objType; // What type of Object this is

	bool _toRemove; // Is this object marked for removal?
};
