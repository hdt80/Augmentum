#ifndef _FPS_H
#define _FPS_H

#include <SFML/System.hpp>

class FPS { 
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// FPS Ctor
    FPS() : frame(0), fps(0) {}

	// Methods /////////////////////////////////////////////////////////////////

    // Must be called after each frame is rendered
    void update();

	// Get the current FPS
	// returns: fps
	inline unsigned int getFPS() const { return fps; }

private:
    unsigned int frame;
    unsigned int fps;
    sf::Clock clock;
};


#endif
