#include "ParticleEmitter.h"

#include <random>

#include "Logger.h"
#include "Random.h"
#include "Convert.h"

ParticleEmitter::ParticleEmitter() {
	_vertices.setPrimitiveType(sf::Points);
}

ParticleEmitter::~ParticleEmitter() {
	_particles.clear();
	_vertices.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////

void ParticleEmitter::emit(ParticleDef* pDef,
		float x, float y, int amt, int angle) {

	// Resize both vectors
	_particles.resize(_particles.size() + amt);
	_vertices.resize(_vertices.getVertexCount() + amt);

	// Only start where we added more particles
	for (unsigned int i = _particles.size() - amt; i < _particles.size(); ++i) {

		float dirAng;
		if (angle >= 0) {
			// Random angle between the angle and the dispersion
			dirAng = Random::randInt(-pDef->coneOfDispersion / 2.0f,
					pDef->coneOfDispersion / 2.0f) + angle;
		} else {
			dirAng = Random::randInt(0, 360);
		}

		dirAng = convert::toRad(dirAng);

		_particles[i].pDef = pDef;
		_particles[i].lifeLeft = _particles[i].pDef->lifetime;
		_particles[i].done = false;
		_particles[i].velocity = sf::Vector2f(std::cos(dirAng) * pDef->speed,
				std::sin(dirAng) * pDef->speed);

		_vertices[i].position = sf::Vector2f(x, y);
		_vertices[i].color = pDef->initColor;
	}
}

// Update all the particles in this Emitter
// diff - Milliseconds since last call
void ParticleEmitter::update(int diff) {
	for (unsigned int i = 0; i < _particles.size(); ++i) {
		if (_particles[i].done == false) {
			Particle& p = _particles[i];
			p.lifeLeft -= diff * 0.000001f;

			if (p.lifeLeft <= 0.0f) {
				p.done = true;
				// TODO: Proper removal
				_vertices[i] = sf::Vertex();
			}

			float ratioDone = p.lifeLeft / p.pDef->lifetime;

			_vertices[i].position += p.velocity * (float)diff * 0.000001f;
			if (p.pDef->slowDown) {
				p.velocity /= ratioDone;
			}
			if (p.pDef->fade) {
				_vertices[i].color.a = ratioDone * 255;
			}
		}
	}
}

void ParticleEmitter::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

	states.transform *= getTransform(); // Apply transformation
	states.texture = nullptr; // No texture
	target.draw(_vertices, states);
}
