#include "PauseWindow.h"

#include "Game.h"
#include "Logger.h"

PauseWindow::PauseWindow(Vector2 size) {
	_size = size;
	_name = "Paused";
	_drawn = false;
}

PauseWindow::~PauseWindow() {

}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////
void PauseWindow::init() {
	Window::init();
	_box.setSize(sf::Vector2f(_size.X, _size.Y));
	_box.setFillColor(sf::Color(128, 128, 128, 128));
}

void PauseWindow::keyEvent(sf::Event& e) {
	if (e.key.code == sf::Keyboard::Pause) {
		Game::WindowManager.pop();
	}
}

void PauseWindow::render(sf::RenderWindow& window) {
	if (!_drawn) {
		window.draw(_box);
		_drawn = true;
	}
}

void PauseWindow::pause() {
	Window::pause();
	_drawn = false;
}
