#ifndef _SKILL_TREE_WINDOW_H
#define _SKILL_TREE_WINDOW_H

#include "Window.h"
#include "Vector2.h"

class SkillTree;

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

	// Window initalization
	virtual void init();

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
	
	SkillTree* _tree; // The SkillTree to draw
};

#endif
