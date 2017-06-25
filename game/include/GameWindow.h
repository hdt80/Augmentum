#pragma once

#include "game/Window.h"
#include "game/Map.h"
#include "game/ParticleEmitter.h"
#include "game/Vector2.h"
#include "game/Cursor.h"
#include "game/SkillTreeWindow.h"

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
	// Vars ////////////////////////////////////////////////////////////////////
	
	Cursor _cursor; // Cursor drawn to the Window

	bool _drawFps; // Draw the FPS counter
	sf::Text _fpsText; // FPS text to draw
	sf::Text _particleCountText; // Text displaying how many particles there are
};
