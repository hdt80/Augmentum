#include "Window.h"

#include "Logger.h"
#include "gui/GuiComponent.h"
#include "Game.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
Window::Window(const std::string& name, Vector2 size) 
	: _name(name), _size(size), _currState(Uninitalized),
		_drawCompBounds(false) {

}

Window::Window()
	: Window("DEFAULT", Vector2(0.0f, 0.0f)) {

}

Window::~Window() {

}

///////////////////////////////////////////////////////////////////////////////
// State Methods
///////////////////////////////////////////////////////////////////////////////

void Window::init() {
	if (_currState != Uninitalized) {
		CORE_ERROR("[%s] Already initalized. Cannot init", _name.c_str());
		return;
	}
	setState(Paused);
	CORE_INFO("[%s] Initalized", _name.c_str());
}

void Window::reset() {
	if (_currState != Running) {
		CORE_WARNING("[%s] Not running. Resetting anyways", _name.c_str());
	}
	CORE_INFO("[%s] Reset", _name.c_str());
}

void Window::pause() {
	if (_currState != Running) {
		CORE_ERROR("[%s] Not running. Cannot pause", _name.c_str());
		return;
	}
	setState(Paused);
	CORE_INFO("[%s] Paused", _name.c_str());
}

void Window::resume() {
	if (_currState != Paused) {
		CORE_ERROR("[%s] Not paused and attempted to resume", _name.c_str());
		return;
	}
	setState(Running);
	CORE_INFO("[%s] Resuming", _name.c_str());
}

void Window::close() {
	if (_currState != Paused) {
		CORE_WARNING("[%s] CLOSING WHILE NOT PAUSED.", _name.c_str());
	}
	CORE_INFO("[%s] Marked for removal", _name.c_str());
}

void Window::setState(WindowState state) {
	CORE_INFO("[%s] State change (%s -> %s)", _name.c_str(),
		getStateString(_currState).c_str(), getStateString(state).c_str());
	_currState = state;
}

std::string Window::getStateString() const {
	return getStateString(_currState);
}

std::string Window::getStateString(WindowState state) const {
	if (state == Running) {
		return "Running";
	} else if (state == Paused) {
		return "Paused";
	} else if (state == Uninitalized) {
		return "Uninitalized";
	} else {
		return "INVALID";
	}
}

void Window::addComponent(GuiComponent* comp, int depth) {
	// TODO: Depth
	_components.push_back(comp);
}

GuiComponent* Window::getComponentAt(float x, float y) {
	for (unsigned int i = 0; i < _components.size(); ++i) {
		if (_components[i]->hasClicked(x, y)) {
			return _components[i];
		}
	}
	return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
// Updating Methods
///////////////////////////////////////////////////////////////////////////////

void Window::update(int diff) {
	for (GuiComponent* comp : _components) {
		if (comp->isUpdating()) {
			comp->update(diff);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Event Methods
///////////////////////////////////////////////////////////////////////////////

void Window::handleEvent(sf::Event& e) {
	if (e.type == sf::Event::Closed) {
		CORE_WARNING("[%s] Given sf::Event::Closed. Discarding", _name.c_str());
	} else if (e.type == sf::Event::KeyPressed) {
		keyEvent(e);
	} else if (e.type == sf::Event::MouseButtonReleased) {
		mouseEvent(e);
	} else if (e.type == sf::Event::MouseMoved) {
		mouseMoveEvent(e);
	} else if (e.type == sf::Event::Resized) {
		resizeEvent(e);
	}
}

void Window::keyEvent(sf::Event& e) {
	if (e.key.code == sf::Keyboard::Pause) {
		Game::pause();
	}
	if (e.key.code == sf::Keyboard::H) {
		_drawCompBounds = !_drawCompBounds;	
	}
}

void Window::mouseEvent(sf::Event& e) {
	GuiComponent* clicked = 
		getComponentAt(e.mouseButton.x, e.mouseButton.y);

	// Ensure there is a GuiComponent we clicked on
	if (clicked != nullptr) {
		// Mouse relative to the window
		sf::Vector2i pixelPos = sf::Mouse::getPosition(Game::getRenderWindow());
		// Mouse relative to the clicked GuiComponent
		sf::Vector2f worldPos = Game::getRenderWindow()
			.mapPixelToCoords(pixelPos, clicked->getView());
		clicked->onClick(e.mouseButton.button,
			pixelPos.x, pixelPos.y, worldPos.x, worldPos.y);
	}
}

void Window::mouseMoveEvent(sf::Event& e) {
	if (_drawCompBounds) {
		_hoveredComp = getComponentAt(e.mouseButton.x, e.mouseButton.y);
	}
}

void Window::resizeEvent(sf::Event& e) {}

void Window::render(sf::RenderWindow& target) {
	for (GuiComponent* comp : _components) {
		if (comp->isVisible()) {
			// Drawing a component relative to its origin and not the screen's
			target.setView(comp->getView());
			target.draw(*comp);
		}
	}

	// After drawing all components reset where we're drawing to
	target.setView(target.getDefaultView());
}
