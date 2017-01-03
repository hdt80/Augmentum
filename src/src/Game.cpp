#include "Game.h"
#include "Logger.h"
#include "GameWindow.h"
#include "ExperienceHelper.h"

void Game::start() {
	if (CurrentGameState != Uninitalized) {
		CORE_ERROR("Attempted to start an initalized gamed");
		return; 
	}

	// Set the antialiasing of the game
	sf::VideoMode currVidMode = sf::VideoMode::getDesktopMode();
	sf::ContextSettings currVidSettings;
	currVidSettings.antialiasingLevel = 8;

	_size.X = 900; _size.Y = 600;

	_window.create(sf::VideoMode(_size.X, _size.Y, currVidMode.bitsPerPixel),
		"Augmentum", sf::Style::Default, currVidSettings);

	// We don't wanna see Window's cursor above our own
	_window.setMouseCursorVisible(false);

	b2DebugDrawer.setRenderWindow(&_window);
	DebugConsole.setPosition(_size);
	ExperienceHelper::populateList();

	_pauseWindow.setSize(_size);

	CurrentGameState = Playing;

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
			} else if (e.type == sf::Event::KeyPressed
				|| e.type == sf::Event::TextEntered) { // TODO: Ew

				if (e.type == sf::Event::KeyPressed) {
					if (e.key.code == sf::Keyboard::Escape
						|| e.key.code == sf::Keyboard::Pause
						|| e.key.code == Console::HOTKEY) {

						Game::handleKeyPress(e);
					} else {
						if (Game::DebugConsole.isOpened()) {
							Game::DebugConsole.handleEvent(e);
						} else {
							CurrentWindow->handleEvent(e);
						}
					}
				} else {
					if (Game::DebugConsole.isOpened()) {
						Game::DebugConsole.handleEvent(e);
					}
				}
			} else {
				CurrentWindow->handleEvent(e);
			}
		}

		// Perform all the updating

		// If the console is opened don't update the game
		if (!Game::DebugConsole.isOpened()) {
			CurrentWindow->update(tDiff);
		}
		CurrentWindow->render(_window);
		if (Game::DebugConsole.isOpened()) {
			_window.draw(Game::DebugConsole);
		}
		Fps.update();
		_window.display();
	}
}

void Game::handleKeyPress(const sf::Event& e) {
	if (e.type != sf::Event::KeyPressed
		&& e.key.code != sf::Keyboard::Escape
		&& e.key.code != sf::Keyboard::Pause
		&& e.key.code != Console::HOTKEY) {
		
		return;
	}

	// Handle the Escape key being push
	if (e.key.code == sf::Keyboard::Escape) {
		if (e.key.shift) {
			CurrentGameState = Ending;
		} else {
			WindowManager.pop();
		}
	} else if (e.key.code == sf::Keyboard::Pause) {
		Game::pause();
	} else if (e.key.code == Console::HOTKEY) {
		Game::DebugConsole.setOpened(!Game::DebugConsole.isOpened());	
	} else {
		CORE_WARN("Invalid key press handled by Game: %d", e.key.code);
	}

}

void Game::followWindow(Window* w) {
	WindowManager.push(w);
	CurrentWindow = w;
	CORE_DEBUG("[Game] CurrentWindow Name: %s",
		CurrentWindow->getName().c_str());
	_window.setTitle(CurrentWindow->getName());
}

void Game::pause() {
	if (CurrentWindow != &_pauseWindow) {
		followWindow(&_pauseWindow);
	} else {
		WindowManager.pop();
	}
}

////////////////////////////////////////////////////////////////////////////////
// Static vars
////////////////////////////////////////////////////////////////////////////////

Game::GameState Game::CurrentGameState = Uninitalized;
Window*			Game::CurrentWindow    = nullptr;
StateManager	Game::WindowManager;

DebugDrawer Game::b2DebugDrawer;
Console		Game::DebugConsole;

FPS Game::Fps;

////////////////////////////////////////////////////////////////////////////////
// Procted vars
////////////////////////////////////////////////////////////////////////////////

sf::RenderWindow Game::_window;
PauseWindow		 Game::_pauseWindow;
Vector2			 Game::_size;
