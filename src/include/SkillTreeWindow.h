#ifndef _SKILL_TREE_WINDOW_H
#define _SKILL_TREE_WINDOW_H

#include "Window.h"
#include "Vector2.h"

class SkillTree;

class SkillTreeWindow : public Window {
public:
	SkillTreeWindow(SkillTree* tree, Vector2 size = Vector2(0.0f, 0.0f));
	~SkillTreeWindow();

	// Window initalization
	virtual void init();

	virtual void update(int diff);

	virtual void keyEvent(sf::Event& e);
	virtual void mouseEvent(sf::Event& e);

	virtual void render(sf::RenderWindow& window);

protected:
	SkillTree* _tree;
};

#endif
