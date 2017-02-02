#include "MainMenuWindow.h"

#include "Game.h"
#include "GameWindow.h"

#include "gui/GuiComponent.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

MainMenuWindow::MainMenuWindow(GameWindow* playWindow, Vector2 size)
	: Window("Main Menu", size) {

	_toolbar = new GuiComponent(this,
		&Databases::GuiEntryStyleDatabase.get("world"),
		&Databases::GuiComponentStyleDatabase.get("style"),
		Vector2(0.0f, 0.0f), size);

	_toolbar->addEntry(new GuiWindowButton(_toolbar, "Play", playWindow),
		(size.X / 2) - _toolbar->getEntryStyle()->getDimensions().X / 2.0f,
		(size.Y / 2) - _toolbar->getEntryStyle()->getDimensions().Y / 2.0f);

	addComponent(_toolbar);
}

MainMenuWindow::~MainMenuWindow() {
	delete _toolbar;
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void MainMenuWindow::update(int diff) {
	Window::update(diff);
	_cursor.update(diff);
}

void MainMenuWindow::render(sf::RenderWindow& window) {
	Window::render(window);
	window.draw(_cursor);
}
