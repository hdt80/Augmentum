#ifndef _GAME_WINDOW_H
#define _GAME_WINDOW_H

#include "Window.h"
#include "Map.h"
#include "ParticleEmitter.h"
#include "Vector2.h"
#include "Cursor.h"

class GameWindow : public Window {
public:

	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// GameWindow ctor
	// size - Size of the render in pixels
	GameWindow(Vector2 size = Vector2(0.0f, 0.0f));

	// GameWindow dtor
	~GameWindow();

	// Methods /////////////////////////////////////////////////////////////////

	// Initalize the window
	virtual void init();

	// Reinit the Window
	// Reinitalize the Window and reset it to default values
	virtual void reset();

	// Close the Window, it is no longer being used
	// Clean up everything and deallocate all associated objects
	virtual void close();

	// Update the Window
	// diff is the amount of microseconds that have passed since the last call
	virtual void update(int diff);

	// Event methods
	virtual void keyEvent(sf::Event& e);
	virtual void mouseEvent(sf::Event& e);

	// Inherited from Window
	virtual void render(sf::RenderWindow& window);
	
	// Static vars /////////////////////////////////////////////////////////////

	static ParticleEmitter Emitter;

protected:

	ParticleDef def;

	Cursor _cursor;

	bool _drawFps; // Draw the FPS counter
	sf::Text _fpsText; // FPS text to draw
	sf::Text _particleCountText; // Text displaying how many particles there are
};

#endif
