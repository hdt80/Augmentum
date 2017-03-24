#ifndef _SKILL_GRID_WINDOW_H
#define _SKILL_GRID_WINDOW_H

#include "Window.h"
#include "Cursor.h"

class SkillGrid;

class SkillGridWindow : public Window {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// SkillGridWindow ctor. This will generate the sf::VertexArrays that are
	//		used to draw the SkillGrid to the sf::RenderWindow
	// grid - SkillGrid that this SkillGridWindow will draw
	SkillGridWindow(SkillGrid* grid);

	// SkillGridWindow dtor
	~SkillGridWindow();

	// Methods /////////////////////////////////////////////////////////////////

	// Pause the window, stop updating
	// Called when we change our current Window to another one
	virtual void pause();

	// Update the SkillGridWindow
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

	// Static vars /////////////////////////////////////////////////////////////
	
	static unsigned int WIDTH; // Width of the SkillGrid in pixels
	static unsigned int HEIGHT; // Height of the SkillGrid in pixels
	static unsigned int NODE_WIDTH; // Width of a single GridNode in pixels
	static unsigned int NODE_HEIGHT; // Height of a single GridNode in pixels

protected:
	// Methods /////////////////////////////////////////////////////////////////
	
	// Generate the sf::VertexArrays used to draw the nodes
	void generateVertexArrays();

	// Vars ////////////////////////////////////////////////////////////////////
	
	bool _backgroundDrawn; // If the background has been drawn yet
	sf::RectangleShape _background; // Background

	sf::VertexArray _nodeLines; // Lines between GridNodes
	sf::VertexArray _nodeBoxes; // Boxes that represent the GridNodes

	Cursor _cursor; // Cursor drawn

	// SkillGrid the SkillGridWindow will draw to the screen
	SkillGrid* _grid;
};

#endif
