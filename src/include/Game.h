#ifndef _GAME_H
#define _GAME_H

#include <SFML/Graphics.hpp>
#include <chrono>

#include "Window.h"
#include "PauseWindow.h"
#include "StateManager.h"
#include "Vector2.h"
#include "FPS.h"
#include "DebugDraw.h"
#include "Database.h"

#define REFRESH_RATE 16666 // 60 FPS - 16.666ms between each frame

class Game {
public:
	// Uninitalized - Game hasn't started. We've just loaded the game
	// Paused - There is no pause Window, instead that is controlled by Game
	// Played - Current Window is active and updates are happening
	// Ending - Game is being closed, start deallocating everything
	enum GameState {Uninitalized, Paused, Playing, Ending};
	
	// Start running the game
	static void start();
	// Main game loop
	static void loop();

	// If the Game is already paused unpause, else pause it
	static void pause();

	// Get if the game is currently shutting down
	static bool toClose() { return CurrentGameState == Ending; }
	// Set the current GameSate
	static void setState(GameState state) { CurrentGameState = state; }

	// Add a new Window to the StateManager and begin updating that one
	static void followWindow(Window* w);

	// Get the sf::RenderWindow that we draw everything to
	static sf::RenderWindow& getRenderWindow() { return _window; }

	static GameState CurrentGameState;
	static Window* CurrentWindow;
	static StateManager WindowManager;

	static FPS Fps;

	static DebugDrawer b2DebugDrawer;

protected:
	static sf::RenderWindow _window;
	static PauseWindow _pauseWindow; // Global pause window
	static Vector2 _size;
};

#endif
