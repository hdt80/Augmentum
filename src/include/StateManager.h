#ifndef _STATE_MANAGER_H
#define _STATE_MANAGER_H

#include <vector>

#include "Window.h"

class Game;

class StateManager {
public:
	StateManager();
	~StateManager();

	// Register what Game we'll be managing
	void registerGame(Game* game);

	// Is the State stack empty?
	bool empty();
	void print();

	// Reset the current State by calling restart()
	void resetCurrentState();

	// Return the top of the stack, the current State
	Window* getCurrentState();

	// Set the current State to that state
	// If that State exists in our stack keep popping until we hit it
	void push(Window* state);

	// Pop the top Window off the stack and move to the next one
	void pop();

private:
	Game* _game;

	std::vector<Window*> _stack; // First In, Last Out
	// Moving up a Window moves up back to the previous one, or up one 
	// in the stack. If a Window is attempted to be added (And set to that)
	// and if it's already in the stack we'll keep popping off Windows till
	// we reach that Window.
	// All Windows below the top one should be in the Paused state
	// Note: Two Windows of the same kind, may exist, such as two GameWindows, 
	// but they cannot share the same addresses and cannot be at the same 
	// addresses. Each Window in the stack is unique
};

#endif