#include "Game.h"
#include "Logger.h"
#include "GameWindow.h"
#include "ExperienceHelper.h"

void Game::start() {
	if (CurrentGameState != Uninitalized) {
		CORE_ERROR("Attempted to start an initalized gamed");
		return; 
	}

	sf::VideoMode currVidMode = sf::VideoMode::getDesktopMode();
	sf::ContextSettings currVidSettings;
	currVidSettings.antialiasingLevel = 8;

	_size.X = 900; _size.Y = 600;

	_window.create(sf::VideoMode(900, 600, currVidMode.bitsPerPixel),
		"Augmentum", sf::Style::Default, currVidSettings);

	_window.setMouseCursorVisible(false);

	b2DebugDrawer.setRenderWindow(&_window);

	CurrentGameState = Playing;

	ExperienceHelper::populateList();

	_pauseWindow.setSize(_size);

	loop();
}

void Game::loop() {
	// Set up timing vars
	std::chrono::time_point<std::chrono::high_resolution_clock> tStart, tEnd;
	tStart = std::chrono::high_resolution_clock::now();
	long long tDiff;

	// Create the first window
	GameWindow w(_size);

	followWindow(&w);

	// Main loop
	sf::Event e;
	while (!toClose()) {
		tEnd = tStart;
		tStart = std::chrono::high_resolution_clock::now();
		tDiff = std::chrono::duration_cast
			<std::chrono::microseconds>(tStart - tEnd).count();

		// Poll all sf::Events and send them to the Window
		while (_window.pollEvent(e)) {
			// If we're closing (e.g. hit close button) don't let the window
			// handle it, we've got it
			// Likewise, Escape is a hardcoded key that Window's aren't allowed
			// to handle, only the Game can do that. If Shift is pressed at the
			// same time don't go up a level, quit the whole game
			// Likewise, Pause is another hardcoded key to open the PauseWindow
			if (e.type == sf::Event::Closed) {
				CurrentGameState = Ending;
			} else if (e.type == sf::Event::KeyPressed &&
				e.key.code == sf::Keyboard::Escape) {
				
				// If Shift is pressed in this sf::Event
				if (e.key.shift) {
					CurrentGameState = Ending;
				} else {
					WindowManager.pop();
				}
			} else {
				CurrentWindow->handleEvent(e);
			}
		}

		CurrentWindow->update(tDiff);
		CurrentWindow->render(_window);
		Fps.update();
		_window.display();
	}
}

//
void Game::followWindow(Window* w) {
	WindowManager.push(w);
	CurrentWindow = w;
	CORE_DEBUG("[Game] CurrentWindow Name: %s",  CurrentWindow->getName().c_str());
	std::string s = CurrentWindow->getName();
	const char* str = s.c_str();
	sf::String sr(str);
	_window.setTitle(sr);
}

//
void Game::pause() {
	if (CurrentWindow != &_pauseWindow) {
		followWindow(&_pauseWindow);
	} else {
		WindowManager.pop();
	}
}

///////////////////////////////////////////////////////////////////////////////
// Static vars
///////////////////////////////////////////////////////////////////////////////
Game::GameState Game::CurrentGameState = Uninitalized;
Window*			Game::CurrentWindow    = nullptr;

DebugDrawer  Game::b2DebugDrawer;
StateManager Game::WindowManager;

FPS Game::Fps;

// Procted vars
sf::RenderWindow Game::_window;
PauseWindow		 Game::_pauseWindow;
Vector2			 Game::_size;
