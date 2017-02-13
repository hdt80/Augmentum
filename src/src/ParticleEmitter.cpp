#include "ParticleEmitter.h"

#include <algorithm>

#include "Logger.h"
#include "Game.h"
#include "Databases.h"

#include "util/Random.h"
#include "util/MathUtil.h"

////////////////////////////////////////////////////////////////////////////////
// ParticleEmitter
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ParticleEmitter ctor and dtor
////////////////////////////////////////////////////////////////////////////////

ParticleEmitter::ParticleEmitter() {

}

ParticleEmitter::~ParticleEmitter() {
	_particles.clear();
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void ParticleEmitter::emit(const ParticleDef* pDef, float x, float y, int amt,
	float angle) {

	_particles.push_back(ParticleGroup(pDef, x, y, amt, angle));
}

void ParticleEmitter::emit(const std::string& name, float x, float y, int amt,
	float angle) {

	const ParticleDef* pDef = &Databases::ParticleDefs.get(name);

	emit(pDef, x, y, amt, angle);
}

void ParticleEmitter::update(int diff) {
	for (ParticleGroup& group : _particles) {
		group.update(diff);

		if (group.done()) {
			// I'm not really sure when we could iterate over the group
			// but not have it be in the vector after an update, but hey,
			// safe practices
			std::vector<ParticleGroup>::iterator it;
			it = std::find(_particles.begin(), _particles.end(), group);
			if (it != _particles.end()) {
				_particles.erase(it);
			} else {
				CORE_ERROR("[ParticleEmitter] Failed to remove done group.");
			}
		}
	}
}

int ParticleEmitter::getParticleCount() const {
	int total = 0;
	for (const ParticleGroup& group : _particles) {
		total += group.getAmount();
	}

	return total;
}

void ParticleEmitter::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

	for (ParticleGroup group : _particles) {
		target.draw(group);
	}
}

////////////////////////////////////////////////////////////////////////////////
// ParticleGroup
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ParticleGroup ctor and dtor
////////////////////////////////////////////////////////////////////////////////

ParticleGroup::ParticleGroup(const ParticleDef* def, float x, float y, int amt,
	float angle)
		: _particleDef(def), _x(x), _y(y), _amount(amt), _angle(angle) {

	_vertices.setPrimitiveType(sf::Points);

	// Resize both vectors to hold all the particles being created
	_particles.resize(amt);
	_vertices.resize(amt);

	for (int i = 0; i < amt; ++i) {
		float rSpeed = def->getSpeed() +
			Random::randInt(-def->getSpeedVariation(), def->getSpeedVariation());

		float dirAng;
		if (angle >= 0) {
			// Random angle between the angle and the dispersion
			dirAng = Random::randInt(-def->getConeOfDispersion() / 2.0f,
				def->getConeOfDispersion() / 2.0f) + angle;
		} else {
			dirAng = Random::randInt(0, 360);
		}

		dirAng = MathUtil::degToRad(dirAng);

		_particles[i].pDef = def;
		_particles[i].lifeLeft = _particles[i].pDef->getLifetime();
		_particles[i].done = false;
		_particles[i].velocity = sf::Vector2f(std::cos(dirAng) * rSpeed,
				std::sin(dirAng) * rSpeed);

		_vertices[i].position = sf::Vector2f(x, y);
		_vertices[i].color = def->getInitColor();
	}
}

ParticleGroup::~ParticleGroup() {
	_particles.clear();
	_vertices.clear();
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloads
////////////////////////////////////////////////////////////////////////////////

bool ParticleGroup::operator==(const ParticleGroup& o) const {
	return (_particleDef == o._particleDef
		&& _x == o._x
		&& _y == o._y
		&& _amount == o._amount
		&& _angle == o._angle);
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void ParticleGroup::update(int diff) {
	for (unsigned int i = 0; i < _particles.size(); ++i) {
		if (_particles[i].done == false) {
			Particle& p = _particles[i];
			p.lifeLeft -= diff * 0.000001f;

			if (p.lifeLeft <= 0.0f) {
				p.done = true;
				
				// Replace the done particle with a clear vertex
				_vertices[i] = sf::Vertex();
			}

			float ratioDone = p.lifeLeft / p.pDef->getLifetime();

			_vertices[i].position += p.velocity * (float)diff * 0.000001f;
			if (p.pDef->isSlowDown()) {
				p.velocity /= ratioDone;
			}
			if (p.pDef->isFade()) {
				_vertices[i].color.a = ratioDone * 255;
			}
		}
	}
}

bool ParticleGroup::done() const {
	for (const Particle& p : _particles) {
		if (!p.done) {
			return false;
		}
	}
	return true;
}

void ParticleGroup::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

	states.transform *= getTransform(); // Apply transformation
	states.texture = nullptr; // No texture
	target.draw(_vertices, states);
}
