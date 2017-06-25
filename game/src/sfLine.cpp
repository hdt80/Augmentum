#include "game/sfLine.h"

#include <cmath>

///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
sfLine::sfLine(const sf::Vector2f& p1, const sf::Vector2f& p2, float t, 
	sf::Color c) : thickness(t), color(c) {

	sf::Vector2f dir = p2 - p1;
    sf::Vector2f unitDir = dir / std::sqrt(dir.x * dir.x + dir.y * dir.y);
    sf::Vector2f unitPerpendicular(-unitDir.y, unitDir.x);

    sf::Vector2f offset = (thickness/2.f) * unitPerpendicular;

    vertices[0].position = p1 + offset;
    vertices[1].position = p2 + offset;
    vertices[2].position = p2 - offset;
    vertices[3].position = p1 - offset;

    for (int i = 0; i < 4; ++i) {
        vertices[i].color = color;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////
void sfLine::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(vertices, 4, sf::Quads);
}
