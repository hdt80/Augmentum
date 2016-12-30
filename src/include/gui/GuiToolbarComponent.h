#ifndef _GUI_TOOLBAR_COMPONENT_H
#define _GUI_TOOLBAR_COMPONENT_H

#include "Vector2.h"
#include "GuiComponent.h"

class GuiToolbarComponent : public GuiComponent {
public:
	// GuiComponent ctor
	// entryStyle - GuiStyle to use when creating our entries
	// compStyle - How to draw our background
	// pos - Where on the screen this component should start (pixels)
	// size - How much of the screen this component takes up (pixels)
	// vert - If all the GuiEntries are aligned vertically
	GuiToolbarComponent(Window* window, const GuiEntryStyle* entryStyle,
			const GuiComponentStyle* comStyle,
			Vector2 pos, Vector2 size, bool vert);
	virtual ~GuiToolbarComponent();

	virtual void addEntry(GuiEntry* entry, float x = 0, float y = 0);

protected:
	bool _vertical; // If all the GuiEntries are aligned vertically
};

#endif
