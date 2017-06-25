#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class FPS : public sf::Drawable {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// FPS Ctor
    FPS();

	// Methods /////////////////////////////////////////////////////////////////

    // Must be called after each frame is rendered
    void update();

	// Get the current FPS
	// returns: fps
	inline unsigned int getFPS() const { return _fps; }

	// Check if the FPS counter is currently visible
	// returns: _visible
	inline bool isVisible() const { return _visible; }

	// Set of the FPS counter is visible or not
	// vis - Is the FPS counter visible
	inline void setVisible(bool vis) { _visible = vis; }

	// Inherited from sf::Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	// Vars ////////////////////////////////////////////////////////////////////
	
    unsigned int _frame; // Current frame being drawn
    unsigned int _fps; // Current frames per second

	sf::Text _fpsText; // Text to draw the FPS

    sf::Clock clock; // Clock to measure FPS

	bool _visible; // If the FPS is being drawn
};
