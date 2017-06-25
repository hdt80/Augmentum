#pragma once

#include "game/Window.h"
#include "game/Map.h"
#include "game/Vector2.h"

class PauseWindow : public Window {
public:
	// PauseWindow ctor and dtor ///////////////////////////////////////////////
	
	// PauseWindow ctor
	// size - Size of the Window in pixels
	PauseWindow(Vector2 size = Vector2(0.0f, 0.0f));

	// PauseWindow dtor
	~PauseWindow();

	// Methods /////////////////////////////////////////////////////////////////

	// Initalize the window
	virtual void init();

	// Pause the window, stop updating
	virtual void pause();

	// Event methods ///////////////////////////////////////////////////////////
	
	// SFML Event handler
	// e - Key event
	virtual void keyEvent(sf::Event& e);

	// Render to a window
	// window - Window to draw to
	virtual void render(sf::RenderWindow& window);

protected:

	sf::RectangleShape _box; // Background to draw

	bool _drawn; // If we've drawn ourselves yet
};
