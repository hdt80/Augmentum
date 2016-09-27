#ifndef _DEBUG_WORLD_COMPONENT_H
#define _DEBUG_WORLD_COMPONENT_H

#include "GuiComponent.h"
#include "Map.h"

class DebugWorldComponent : public GuiComponent {
public:
	DebugWorldComponent(Window* window, GuiStyle* style, Vector2 pos,
			Vector2 size, Vector2 windowSize);

	virtual void update(int diff);
	void draw(sf::RenderTarget&, sf::RenderStates) const;

private:
	Map* _map;
};

#endif
