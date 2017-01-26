#include "StateManager.h"

#include "Logger.h"
#include "Game.h"

///////////////////////////////////////////////////////////////////////////////
// StateManager ctor and dtor
//////////////////////////////////////////////////////////////////////////////

StateManager::StateManager() {
	_game = nullptr;
}

StateManager::~StateManager() {
	_game = nullptr;	
}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////

void StateManager::registerGame(Game* game) {
	if (_game != nullptr) {
		CORE_ERROR("A Game is already registerd in StateManager");
		return;
	}
	_game = game;
}

bool StateManager::empty() const {
	return (_stack.size() == 0);
}

void StateManager::print() const {
	CORE_INFO("/ States");
	for (unsigned int i = 0; i < _stack.size(); ++i) {
		CORE_INFO("|%i: %s (%s, %i) @%x", i, _stack[i]->getName().c_str(),
			_stack[i]->getStateString().c_str(),
			_stack[i]->getState(), _stack[i]);
	}
	CORE_INFO("\\\n");
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
		CORE_ERROR("Cannot add state, it's nullptr!");
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
		CORE_WARNING("%s isn't Running and we're popping",
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
