#ifndef SELECTED_COMPONENT_H
#define SELECTED_COMPONENT_H

#include "GuiComponent.h"
#include <memory>

class Tower;
class GameWindow;

class SelectedComponent : public GuiComponent {
public:
	SelectedComponent();
	SelectedComponent(GameWindow* window);
	~SelectedComponent();

	void update(int diff);
	void draw(sf::RenderTarget&, sf::RenderStates) const;

	Tower* getSelected() { return _selected; }
	std::shared_ptr<Tower> getSel() { return _sel; }

private:
	Tower* _selected;
	std::shared_ptr<Tower> _sel;
};

#endif
