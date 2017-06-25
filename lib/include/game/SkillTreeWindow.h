#pragma once

#include "game/Window.h"
#include "game/Vector2.h"
#include "game/Cursor.h"

class SkillTree;
class Unit;

class SkillTreeWindow : public Window {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// SkillTreeWindow ctor
	// tree - Tree that will be drawn
	// size - Size in pixels to draw the Window as
	SkillTreeWindow(SkillTree* tree, Vector2 size = Vector2(0.0f, 0.0f));

	// SkillTreeWindow dtor
	~SkillTreeWindow();

	// Methods /////////////////////////////////////////////////////////////////

	// Pause the window, stop updating
	// Called when we change our current Window to another one
	virtual void pause();

	// Update the SkillTreeWindow
	// diff - Microseconds to update for
	virtual void update(int diff);

	// Occurs when a key is pressed
	// e - Event that holds the data of the key press
	virtual void keyEvent(sf::Event& e);

	// Occurs when a mouse button is pressed
	// e - Event that holds the data of the mouse button press
	virtual void mouseEvent(sf::Event& e);

	// Render the Window to a sf::RenderWindow
	// window - sf::RenderWindow to render to
	virtual void render(sf::RenderWindow& window);

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	bool _backgroundDrawn; // If the background has been drawn yet
	sf::RectangleShape _background; // Background

	Cursor _cursor; // Cursor drawn

	SkillTree* _tree; // The SkillTree to draw
};
