#ifndef _GAME_H
#define _GAME_H

#include <SFML/Graphics.hpp>
#include <chrono>

#include "Window.h"
#include "PauseWindow.h"
#include "StateManager.h"
#include "Vector2.h"
#include "FPS.h"

#define REFRESH_RATE 16666 // 60 FPS - 16.666ms between each frame

class Game {
public:
	// Uninitalized - Game hasn't started. We've just loaded the game
	// Paused - There is no pause Window, instead that is controlled by Game
	// Played - Current Window is active and updates are happening
	// Ending - Game is being closed, start deallocating everything
	enum GameState {Uninitalized, Paused, Playing, Ending};
	
	static void start();
	static void loop();

	// If the Game is already paused unpause, else pause it
	static void pause();

	static bool toClose() { return CurrentGameState == Ending; }
	static void setState(GameState state) { CurrentGameState = state; }

	static void followWindow(Window* w);

	static GameState CurrentGameState;
	static Window* CurrentWindow;
	static StateManager WindowManager;

	static FPS Fps;

protected:
	static sf::RenderWindow _window;
	static PauseWindow _pauseWindow;
	static Vector2 _size;
};

#endif