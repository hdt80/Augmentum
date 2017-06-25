#include "game/StateManager.h"

#include "game/Window.h"
#include "game/Game.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// StateManager ctor and dtor
///////////////////////////////////////////////////////////////////////////////

StateManager::StateManager() {

}

StateManager::~StateManager() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

bool StateManager::empty() const {
	return (_stack.size() == 0);
}

void StateManager::print() const {
	AG_INFO("/ States");
	for (unsigned int i = 0; i < _stack.size(); ++i) {
		AG_INFO("|%i: %s (%s, %i) @%x", i, _stack[i]->getName().c_str(),
			_stack[i]->getStateString().c_str(),
			_stack[i]->getState(), _stack[i]);
	}
	AG_INFO("\\\n");
}

void StateManager::resetCurrentState() {
	_stack[_stack.size()]->reset();
}

Window* StateManager::getCurrentState() {
	if (_stack.size() > 0) {
		return _stack[_stack.size() - 1];
	}
	return nullptr;
}

void StateManager::push(Window* state) {
	if (state == nullptr) {
		AG_ERROR("Cannot add state, it's nullptr!");
		return;
	}

	// Pause the current state
	if (getCurrentState() != nullptr) {
		getCurrentState()->pause();
	}
	
	// If pushed Window hasn't been initalized, do so
	if (state->getState() == Window::WindowState::Uninitalized) {
		state->init();
	}

	state->setState(Window::WindowState::Running);
	_stack.push_back(state);
}

void StateManager::pop() {
	if (getCurrentState()->getState() != Window::WindowState::Running) {
		AG_WARN("%s isn't Running and we're popping",
			getCurrentState()->getName().c_str());
	}

	// Get the current state from the stack
	Window* popped = getCurrentState();
	_stack.pop_back();

	popped->pause();
	popped->close();

	if (getCurrentState() == nullptr) {
		Game::CurrentGameState = Game::GameState::Ending;
	} else {
		getCurrentState()->resume();
		Game::CurrentWindow = getCurrentState();
	}
}
