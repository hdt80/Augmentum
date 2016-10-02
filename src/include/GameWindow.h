#ifndef _GAME_WINDOW_H
#define _GAME_WINDOW_H

#include "Window.h"
#include "Map.h"
#include "ParticleEmitter.h"
#include "Vector2.h"
#include "Cursor.h"

class GameWindow : public Window {
public:
	GameWindow(Vector2 size = Vector2(0.0f, 0.0f));
	~GameWindow();

	// Initalize the window
	virtual void init();

	// Update the Window
	// diff is the amount of microseconds that have passed since the last call
	virtual void update(int diff);

	// Event methods
	virtual void keyEvent(sf::Event& e);
	virtual void mouseMoveEvent(sf::Event& e);

	//
	virtual void render(sf::RenderWindow& window);

	static ParticleEmitter Emitter;

	Map* getMap() { return &_map; }

protected:
	Map _map; // Map the game is played on

	ParticleDef def;

	Cursor _cursor;
};

#endif
