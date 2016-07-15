#ifndef _FPS_H
#define _FPS_H

#include <SFML/System.hpp>

class FPS { 
public:
    FPS() : frame(0), fps(0) {}

    // Must be called after each frame is rendered
    void update();

    const unsigned int getFPS() const { return fps; }

private:
    unsigned int frame;
    unsigned int fps;
    sf::Clock clock;
};


#endif