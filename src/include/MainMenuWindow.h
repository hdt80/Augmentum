#ifndef _MAIN_MENU_WINDOW_H
#define _MAIN_MENU_WINDOW_H

#include "Window.h"
#include "Cursor.h"
#include "gui/GuiWindowButton.h"

class GuiComponent;
class GameWindow;

class MainMenuWindow : public Window {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Ctor for a MainMenuWindow
	// playWindow - Window of the playing game
	// size - Size to make the window
	MainMenuWindow(GameWindow* playWindow, Vector2 size = Vector2(0.0f, 0.0f));

	// MainMenuWindow dtor
	~MainMenuWindow();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Update the MainMenuWindow
	// diff - Microseconds to update for
	virtual void update(int diff);

	// Render to a window
	// window- sf::RenderWindow to render to
	virtual void render(sf::RenderWindow& window);

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	GuiComponent* _toolbar;

	Cursor _cursor;
};

#endif
