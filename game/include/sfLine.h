#ifndef _SFLINE_H
#define _SFLINE_H

#include <SFML/Graphics.hpp>

class sfLine : public sf::Drawable {
public:
    // Thickness cannot be changed after the line is initalized
    sfLine(const sf::Vector2f& point1, const sf::Vector2f& point2, float t, 
        sf::Color c = sf::Color::White);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    sf::Vertex vertices[4];
    float thickness;
    sf::Color color;
};

#endif