#ifndef _DEBUG_WORLD_COMPONENT_H
#define _DEBUG_WORLD_COMPONENT_H

#include "GuiComponent.h"
#include "Map.h"

class DebugWorldComponent : public GuiComponent {
public:
	DebugWorldComponent(Window* window, const GuiEntryStyle* style,
			const GuiComponentStyle* compStyle, Vector2 pos, Vector2 size);

	virtual void update(int diff);

private:
	Map* _map;

	GuiEntry* _fps;
	GuiEntry* _pos;
	GuiEntry* _speed;
	GuiEntry* _mousePos;
};

#endif
