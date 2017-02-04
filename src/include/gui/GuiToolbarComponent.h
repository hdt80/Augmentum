#ifndef _GUI_TOOLBAR_COMPONENT_H
#define _GUI_TOOLBAR_COMPONENT_H

#include "Vector2.h"
#include "GuiComponent.h"

class GuiToolbarComponent : public GuiComponent {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////

	// GuiToolbarComponent ctor
	// window - Window the GuiToolbarComponent is being drawn to
	// entryStyle - GuiStyle to use when creating our entries
	// compStyle - How to draw our background
	// pos - Where on the screen this component should start (pixels)
	// size - How much of the screen this component takes up (pixels)
	// vert - If all the GuiEntries are aligned vertically
	GuiToolbarComponent(Window* window, const GuiEntryStyle* entryStyle,
		const GuiComponentStyle* comStyle,
		Vector2 pos, Vector2 size, bool vert);

	// GuiToolbarComponent dtor
	virtual ~GuiToolbarComponent();

	// Methods /////////////////////////////////////////////////////////////////

	// Add a new GuiEntry to the GuiToolbarComponent
	// entry - Entry to add
	// x - X coord to place the entry at. This value is ignored for a toolbar
	// y - Y coord to place the entry at. This value is ignored for a toolbar
	virtual void addEntry(GuiEntry* entry, float x = 0, float y = 0);

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	bool _vertical; // If all the GuiEntries are aligned vertically
};

#endif
