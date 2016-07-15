#include "ParticleEmitter.h"

#include "Window.h"
#include "Particle.h"
#include "Color.h"

GameWindow* ParticleEmit::window; // Create a reference to the window

namespace ParticleEmit {
	void emit(float x, float y, int amount, Color c) {
		ParticleEmitter* pe = new ParticleEmitter(sf::Vector2f(x, y),
			amount, c.toSF());
		window->emitters.push_back(pe);
	}
}