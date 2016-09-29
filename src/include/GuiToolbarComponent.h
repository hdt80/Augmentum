#ifndef _GUI_TOOLBAR_COMPONENT_H
#define _GUI_TOOLBAR_COMPONENT_H

#include "Vector2.h"
#include "GuiComponent.h"

class GuiToolbarComponent : public GuiComponent {
public:
	// GuiComponent ctor
	// pos - Where on the screen this component should start (pixels)
	// style - GuiStyle to use when creating our entries
	// size - How much of the screen this component takes up (pixels)
	// windowSize - Size of the window this component is a part of (pixels)
	// vert - If all the GuiEntries are aligned vertically
	GuiToolbarComponent(Window* window, GuiEntryStyle* style, Vector2 pos,
			Vector2 size, Vector2 windowSize, bool vert);
	virtual ~GuiToolbarComponent();

	virtual void addEntry(GuiEntry* entry, float x = 0, float y = 0);

protected:
	bool _vertical; // If all the GuiEntries are aligned vertically
};

#endif
