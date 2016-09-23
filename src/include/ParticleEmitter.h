#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Vector2.h"

// Definition of a particle
struct ParticleDef {
	// How many seconds this particle will last for
	float lifetime;

	// When given an angle to emit from how much varience will there be?
	float coneOfDispersion;

	sf::Color initColor; // What color the particles will start with
	sf::Color endColor; // What color the particles will be just before removal
	bool fade; // If the particles will fade the longer they're around

	float speed; // How many pixels/second the particle will move from origin
	bool slowDown; // If the particles should slow down to 0 as they update
};

// Singleton class that does all the updating and emitting
class ParticleEmitter : public sf::Drawable, public sf::Transformable {
public:
	// Ctor and Dtor
	ParticleEmitter();
	~ParticleEmitter();

	// Emit particles
	// pDef - Particle Definition to use when emitting
	// x - X coord to emit from
	// y - Y coord to emit from
	// amt - Amount of particles to add
	// dir - Direction the particles should travel
	void emit(ParticleDef* pDef, float x, float y, int amt, Vector2 dir);

	// Update all particles
	// diff - Microseconds since last update
	void update(int diff);

protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;

	struct Particle {
		ParticleDef* pDef;
		sf::Vector2f velocity;
		sf::Vector2f pos;
		float lifeLeft; // How many more seconds this particle will be around
		bool done;
	};

	// _particles and _vertices should always match size
	std::vector<Particle> _particles;
    sf::VertexArray _vertices;
};

#endif
