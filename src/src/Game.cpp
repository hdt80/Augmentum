#include "Game.h"
#include "Logger.h"

#include "ExperienceHelper.h"

#include "GameWindow.h"
#include "MainMenuWindow.h"

#include <chrono>

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

	DebugConsole.loadLua();

	loop();
}

void Game::loop() {
	// Set up timing vars
	std::chrono::time_point<std::chrono::high_resolution_clock> tStart, tEnd;
	tStart = std::chrono::high_resolution_clock::now();
	long long tDiff;

	// Create the first window
	GameWindow w(_size);

	MainMenuWindow mainMenu(&w, _size);

	followWindow(&mainMenu);

	// Main loop
	while (!toClose()) {
		tEnd = tStart;
		tStart = std::chrono::high_resolution_clock::now();
		tDiff = std::chrono::duration_cast
			<std::chrono::microseconds>(tStart - tEnd).count();
		
		step(tDiff);
	}
}

void Game::step(long long diff) {

	// Event all queued events will get polled into
	sf::Event e;

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
		} else if (DebugConsole.isOpened()) {
			if (e.type == sf::Event::KeyPressed
					&& isReservedKey(e.key.code)) {

				handleKeyPress(e);
			} else {
				DebugConsole.handleEvent(e);
			}
		} else if (e.type == sf::Event::KeyPressed
				&& isReservedKey(e.key.code)) {

			handleKeyPress(e);
		} else {
			CurrentWindow->handleEvent(e);
		}
	}

	// Perform all the updating

	// If the console is opened don't update the game
	if (!Game::DebugConsole.isOpened()) {
		CurrentWindow->update(diff);
	}
	CurrentWindow->render(_window);
	if (Game::DebugConsole.isOpened()) {
		_window.draw(Game::DebugConsole);
	}
	Fps.update();
	_window.display();
}

void Game::handleKeyPress(const sf::Event& e) {
	if (e.type != sf::Event::KeyPressed
		&& !Game::isReservedKey(e.key.code)) {
		
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

bool Game::isReservedKey(const sf::Keyboard::Key& key) {
	return (key == sf::Keyboard::Pause
		|| key == sf::Keyboard::Escape
		|| key == Console::HOTKEY);
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

Map& Game::getMap() {
	// By defining the static Map in a method we avoid the
	// "static initalization order fiasco". This means that map will never
	// get freed, but that's ok
	static Map* map = new Map;
	return *map;
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

namespace Databases {
	Database<sf::Font> FontDatabase;
	Database<GuiEntryStyle> GuiEntryStyleDatabase;
	Database<GuiComponentStyle> GuiComponentStyleDatabase;
	Database<GuiProgressBarStyle> GuiProgressBarStyleDatabase;
	Database<ParticleDef> ParticleDefDatabase;
}
