#include "game/gui/GuiToolbarComponent.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Ctro and dtor
////////////////////////////////////////////////////////////////////////////////

GuiToolbarComponent::GuiToolbarComponent(Window* window,
		const GuiEntryStyle* style, const GuiComponentStyle* compStyle,
		Vector2 pos, Vector2 size, bool vert)
	: GuiComponent(window, style, compStyle, pos, size),
		_vertical(vert) {

}

GuiToolbarComponent::~GuiToolbarComponent() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

// Ignore the x and y coords
void GuiToolbarComponent::addEntry(GuiEntry* entry, float x, float y) {
	float px = 0.0f;
	float py = 0.0f;
	if (_vertical) {
		px = getX();
		py = _guiEntryStyle->getDimensions().Y * _entries.size();
	} else {
		px = _guiEntryStyle->getDimensions().X * _entries.size();
		py = getY();
	}
	entry->setPosition(px, py);
	_entries.push_back(entry);
}
