#ifndef _WINDOW_H
#define _WINDOW_H

#include <SFML/Graphics.hpp>

#include "Vector2.h"

class GuiComponent;

// Window
// A Window is a state the Game is in that determines what game flow
// should be followed. The Game holds what Window we're using and controls
// movement between Windows.
class Window {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	Window(const std::string& name, Vector2 size = Vector2(0.0f, 0.0f));
	virtual ~Window();

	enum WindowState {Running, Paused, Uninitalized};

	// Methods /////////////////////////////////////////////////////////////////

	// Initalize the window.
	// Called when the Window is first pushed onto the state stack and another
	// Window of the same type isn't on the state stack
	// init will be called right before it is made the current state
	// in StateManager
	virtual void init();

	// Reinit the Window
	// Reinitalize the Window and reset it to default values
	virtual void reset();

	// Pause the window, stop updating
	// Called when we change our current Window to another one
	virtual void pause();

	// Resume updating
	// This Window has been initalized but paused
	virtual void resume();

	// Close the Window, it is no longer being used
	// Clean up everything and deallocate all associated objects
	virtual void close();

	// Change the Window's state
	virtual void setState(WindowState state);
	WindowState getState() const { return _currState; }
	std::string getStateString() const;
	std::string getStateString(WindowState state) const;

	// Set the size of the Window
	// size - New size to make the Window
	inline void setSize(const Vector2& size) { _size = size; }

	// Get the size of this Window
	// returns: _size
	inline const Vector2& getSize() const { return _size; }

	// Get the width of the Window
	// returns: _size.Y
	inline int getWidth() const { return _size.X; }

	// Get the height of the Window
	// returns: _size.Y
	inline int getHeight() const { return _size.Y; }

	// Name getter and setter
	const std::string& getName() const { return _name; }
	void setName(const std::string& name) { _name = name; }

	// Update the Window
	// diff is the amount of microseconds that have passed since the last call
	virtual void update(int diff);

	// Event methods
	virtual void handleEvent(sf::Event& e);
	virtual void keyEvent(sf::Event& e);
	virtual void mouseEvent(sf::Event& e);
	virtual void mouseMoveEvent(sf::Event& e);
	virtual void resizeEvent(sf::Event& e);

	// Render to the target window
	virtual void render(sf::RenderWindow&);

	// Get the GuiComp at point x, y
	// x - X coord of the window
	// y - Y coord of the window
	// returns: The first GuiComp at x y, or nullptr if no GuiComp is there
	GuiComponent* getComponentAt(float x, float y);

protected:
	// Nullary ctor
	Window();

	// Add a new GuiComp to this Window
	// comp - GuiComponent to add
	// depth - How far down the GuiComp should be at. Depth of 0 is highest
	void addComponent(GuiComponent* comp, int depth = 0);

	GuiComponent* _hoveredComp; // GuiComp the mouse has hovered over

	std::string _name; // Internal name of the Window, should be unique

	Vector2 _size; // width and height of the Window

	WindowState _currState; // Current state the window is in

	bool _drawCompBounds; // Draw the bounds of the components in this Window?

	std::vector<GuiComponent*> _components; // Components in the Window
};


#endif
