#ifndef _PAUSE_WINDOW_H
#define _PAUSE_WINDOW_H

#include "Window.h"
#include "Map.h"
#include "Particle.h"
#include "Vector2.h"

class PauseWindow : public Window {
public:
	PauseWindow(Vector2 size = Vector2(0.0f, 0.0f));
	~PauseWindow();

	// Initalize the window 
	virtual void init();
	// // Reinit the Window
	// virtual void reset();
	// // Pause the window, stop updating
	virtual void pause();
	// // Resume updating
	// virtual void resume();
	// // Mark the Window for closing
	// virtual void close();

	// Update the Window. 
	// diff is the amount of microseconds that have passed since the last call
	//virtual void update(int diff);

	// Event methods
	//virtual void handleEvent(sf::Event& e);
	virtual void keyEvent(sf::Event& e);
	//virtual void mouseEvent(sf::Event& e);
	//virtual void resizeEvent(sf::Event& e);

	//virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	virtual void render(sf::RenderWindow& window);

protected:
	sf::RectangleShape _box;

	bool _drawn; // If we've drawn ourselves yet
};

#endif
