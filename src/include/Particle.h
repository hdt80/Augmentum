#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class ParticleEmitter : public sf::Drawable, public sf::Transformable {
public:
	ParticleEmitter(sf::Vector2f pos, int amt, sf::Color c = sf::Color::White);
	~ParticleEmitter();

	// Diff is measured in microseconds (1,000,000 in a second)
	void update(int diff);
	bool done(); // If all particles are done and their lifetime is over
protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;

	struct Particle {
		sf::Vector2f velocity;
		bool done;
		float lifetime;
	};

	std::vector<Particle> _particles;
    sf::VertexArray _vertices;
    float _lifetime;
    sf::Vector2f _origin;
};

#endif