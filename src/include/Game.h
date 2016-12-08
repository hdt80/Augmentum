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
	// returns: Tue if the CurrentGameState equals Ending
	static bool toClose() { return CurrentGameState == Ending; }

	// Set the current GameSate
	// state - New state of the Game
	static void setState(GameState state) { CurrentGameState = state; }

	// Add a new Window to the StateManager and begin updating that one
	// w - Window to follow
	static void followWindow(Window* w);

	// Get the sf::RenderWindow that we draw everything to
	// returns: A reference to the SFML RenderWindow used
	static sf::RenderWindow& getRenderWindow() { return _window; }

	static GameState CurrentGameState; // Current state of the game
	static Window* CurrentWindow; // Current Window being drawn
	static StateManager WindowManager; // Window manager

	static FPS Fps; // FPS Counter

	static DebugDrawer b2DebugDrawer; // Debug drawer

protected:
	static sf::RenderWindow _window; // SFML Render being rendered to
	static PauseWindow _pauseWindow; // Global pause window
	static Vector2 _size; // Size of the window
};

#endif
