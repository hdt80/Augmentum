#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

#include "Vector2.h"

class ParticleGroup;
class ParticleDef;

// Singleton class that does all the updating and emitting
class ParticleEmitter : public sf::Drawable, public sf::Transformable {
public:
	// Ctor and Dtor ///////////////////////////////////////////////////////////
	
	// ParticleEmitter ctor
	ParticleEmitter();

	// ParticleEmitter dtor
	~ParticleEmitter();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Emit particles at a position by using a ParticleDef*
	// pDef - Particle Definition to use when emitting. If pDef is nullptr then
	//		no particles will be emitter
	// x - X coord to emit from
	// y - Y coord to emit from
	// amt - Amount of particles to add
	// angle - Angle to shoot the particles at
	//		If angle is < 0, then a random angle between 0-360 is picked for
	//		each particle emitter
	void emit(const ParticleDef* pDef, float x, float y, int amt, float angle);
	
	// Emit particles at a position by using a name lookup
	// name - Name of the ParticleDef to emit. The name lookup is done in
	//		Database::ParticleDefDatabase. If no matching name is found then
	//		the default ParticleDef will be used
	// x - X coord to emit from
	// y - Y coord to emit from
	// amt - Amount of particles to add
	// angle - Angle to shoot the particles at
	//		If angle is < 0, then a random angle between 0-360 is picked
	void emit(const std::string& name, float x, float y, int amt, float angle);

	// Update all particles
	// diff - Milliseconds since last update
	void update(int diff);

	// Get how many particles are currently being rendered
	// returns: The amount of particles stored in _particles
	int getParticleCount() const;

protected:
	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;

	// Vars ////////////////////////////////////////////////////////////////////

	// Particles being drawn
	std::vector<ParticleGroup> _particles;
};

// A ParticleGroup is a group of particles that were emitted at the same time
// A ParticleGroup should only be created from and by ParticleEmitter, as
// the ParticleEmitter manages all ParticleGroup
class ParticleGroup : public sf::Drawable, public sf::Transformable {
public:
	// ParticleGroup ctor and dtor /////////////////////////////////////////////
	
	// Ctor for a ParticleGroup
	// def - Particle Definition to use when emitting
	// x - X coord to emit from
	// y - Y coord to emit from
	// amt - Amount of particles to add
	// ang - Angle in degrees to shoot the particles at. If the angle
	//		is < 0, then a random angle between 0 and 360 is picked
	//		for each particle
	ParticleGroup(const ParticleDef* def, float x, float y, int amt, float ang);

	// ParticleGroup dtor
	~ParticleGroup();

	// Operator overloads //////////////////////////////////////////////////////
	
	// Operator overload for equality checking
	// o - Other ParticleGroup to check for
	// returns: If the two ParticleGroups are the same
	bool operator==(const ParticleGroup& o) const;

	// Methods /////////////////////////////////////////////////////////////////
	
	// Check if this ParticleGroup is finished and should be removed
	// returns: If all the particles in this group are done
	bool done() const;

	// Update all the particles
	// diff - Milliseconds since the last update
	void update(int diff);

	// Get how many particles are used in this group
	// returns: _amount
	inline int getAmount() const { return _amount; }

protected:

	// Represents a single particle that is seen on screen
	struct Particle {
		const ParticleDef* pDef;
		sf::Vector2f velocity;
		float lifeLeft; // How many more seconds this particle will be around
		bool done;
	};

	// Intherited from sf::Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Variables ///////////////////////////////////////////////////////////////

	// Both of these should always have the same number of elements
	// The indexes are matched, so the index in _particles is the sf::Vertex
	// that is in _vertices
	std::vector<Particle> _particles; // Particle that make up this group
	sf::VertexArray _vertices; // Vertices that SFML draws

	// These variables are only used to compare two ParticleGroups
	
	const ParticleDef* _particleDef;
	float _x;
	float _y;
	int _amount;
	float _angle;
};

#endif
