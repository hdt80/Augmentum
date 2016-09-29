#include "GuiToolbarComponent.h"
#include "Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Ctro and dtor
////////////////////////////////////////////////////////////////////////////////

GuiToolbarComponent::GuiToolbarComponent(Window* window, GuiEntryStyle* style,
		Vector2 pos, Vector2 size, Vector2 windowSize, bool vert)
	: GuiComponent(window, style, pos, size, windowSize),
		_vertical(vert) {

}

GuiToolbarComponent::~GuiToolbarComponent() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

// Ignore the x and y coords
void GuiToolbarComponent::addEntry(GuiEntry* entry, float x, float y) {
	// TODO: This
	if (_vertical) {
		CORE_WARN("Vert GuiToolbarComp not added");
	} else {
		float x = _guiEntryStyle->dimensions.X * _entries.size();
		float y = getY();
		entry->setPosition(x, y);
		_entries.push_back(entry);
	}
}
