#include "Particle.h"

#include <random>

#include "Logger.h"

ParticleEmitter::ParticleEmitter(sf::Vector2f pos, int count, sf::Color c) :
	_particles(count),
	_vertices(sf::Points, count),
	_lifetime(3.0f),
	_origin(pos) {

	// Particles can't be created after an emitter is constructed
	// because I don't need to be able to do that
	for (int i = 0; i < count; ++i) {
		// Random angle to off shoot from
		float angle = (std::rand() % 360) * 3.14f / 180.0f;
		float speed = (std::rand() % 50) + 50.0f;

		_particles[i].velocity = sf::Vector2f(std::cos(angle) * speed,
			std::sin(angle) * speed);
		_particles[i].lifetime = _lifetime;

		_vertices[i].position = _origin;
		_vertices[i].color = c;
	}
}

ParticleEmitter::~ParticleEmitter() {
	_particles.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////
void ParticleEmitter::update(int diff) {
	for (unsigned int i = 0; i < _particles.size(); ++i) {
		if (_particles[i].done == false) {
			Particle& p = _particles[i];
			p.lifetime -= diff * 0.000001f;

			if (p.lifetime <= 0.0f) {
				p.done = true;
			}

			_vertices[i].position += p.velocity * (float)diff * 0.000001f;
			float ratio = p.lifetime / _lifetime;
			_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		}
	}
}

bool ParticleEmitter::done() {
	// If any particle isn't done we know we're not done
	for (unsigned int i = 0; i < _particles.size(); ++i) {
		if (_particles[i].done == false) {
			return false;
		}
	}
	return true;
}

void ParticleEmitter::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

	states.transform *= getTransform(); // Apply transformation
	states.texture = nullptr; // No texture
	target.draw(_vertices, states);
}