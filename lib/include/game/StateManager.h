#pragma once

#include <vector>

class Window;

class StateManager {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	StateManager();
	~StateManager();

	// Methods /////////////////////////////////////////////////////////////////

	// Check if the current Window stack is empty
	// returns: _stack.empty()
	bool empty() const;

	// Print all the Windows in the stack
	void print() const;

	// Reset the current State by calling restart()
	void resetCurrentState();

	// Return the top of the stack, the current State
	Window* getCurrentState();

	// Push a new Window onto the stack and initalize it. If that Window already
	//		exists within the stack the StateManager will pop off Windows until
	//		the window is reached
	// state -  Window to push to the stack
	void push(Window* state);

	// Pop the top Window off the stack and move to the next one
	void pop();

private:
	// Vars ////////////////////////////////////////////////////////////////////
	
	// Stack of Windows currently in the Game. Pushing a new Window to the stack
	// will, if not already in the stack, be initalize, and current Window will
	// be paused, and the newly added Window will be drawn and updated. If the
	// Window already exists in the stack Windows will be popped off the stack
	// until that Window is reached. A Window is considered the same if the
	// pointers have the same address
	std::vector<Window*> _stack;
};
