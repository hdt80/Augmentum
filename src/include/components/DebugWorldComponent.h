#ifndef _DEBUG_WORLD_COMPONENT_H
#define _DEBUG_WORLD_COMPONENT_H

#include "gui/GuiComponent.h"
#include "Map.h"

class DebugWorldComponent : public GuiComponent {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	DebugWorldComponent(Window* window, const GuiEntryStyle* style,
			const GuiComponentStyle* compStyle, Vector2 pos, Vector2 size);

	// Methods /////////////////////////////////////////////////////////////////

	virtual void update(int diff);

private:
	// Vars ////////////////////////////////////////////////////////////////////
	Map* _map;

	GuiEntry* _fps;
	GuiEntry* _pos;
	GuiEntry* _speed;
	GuiEntry* _mousePos;
};

#endif
