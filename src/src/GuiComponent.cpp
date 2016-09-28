#include "GuiComponent.h"
#include "Logger.h"
#include "Window.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GuiComponent::GuiComponent(Window* window, GuiStyle* style,
		Vector2 pos, Vector2 size, Vector2 windowSize) {

	// Components start at (0, 0) and not the position because a view represents
	// a view to a part of a drawing target, and we're drawn to (0, 0)
	_view.reset(sf::FloatRect(0, 0, size.X, size.Y));

	_pos = pos;
	_size = size;

	resize(windowSize);

	_visible = true;
	_updating = true;
	_clickable = true;

	_highlightedEntry = nullptr;

	_window = window;
}

GuiComponent::~GuiComponent() {
	_window = nullptr;
	for (GuiEntry* entry : _entries) {
		delete entry;
	}
	_entries.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Update methods
///////////////////////////////////////////////////////////////////////////////

void GuiComponent::update(int diff) {
	sf::Vector2i mousePos = sf::Mouse::getPosition();	
	GuiEntry* hovered = getEntry(mousePos.x, mousePos.y);
	
	if (_highlightedEntry != hovered) {
		if (_highlightedEntry) {
			_highlightedEntry->setHighlighted(false);
		}
		if (hovered) {
			hovered->setHighlighted(true);
		}
		_highlightedEntry = hovered;
	}
}

void GuiComponent::draw(sf::RenderTarget& target,
		sf::RenderStates states) const {

	for (GuiEntry* entry : _entries) {
		target.draw(entry->getShape());
		target.draw(entry->getText());
	}
}

////////////////////////////////////////////////////////////////////////////////
// Bounds methods
////////////////////////////////////////////////////////////////////////////////

bool GuiComponent::contains(float x, float y) {
	return (x >= _pos.X && x <= _size.X + _pos.X &&
			y >= _pos.Y && y <= _size.Y + _pos.Y);
}

bool GuiComponent::hasClicked(float x, float y) {
	if (!_clickable) {
		return false;
	}
	return contains(x, y);
}	

void GuiComponent::addEntry(GuiEntry* entry, float x, float y) {
	entry->setPosition(x, y);
	_entries.push_back(entry);
}

GuiEntry* GuiComponent::getEntry(float x, float y) {
	for (unsigned int i = 0; i < _entries.size(); ++i) {
		GuiEntry* entry = _entries[i];
		if (entry->getX() > x && entry->getX() + _guiStyle.dimensions.X < x &&
			entry->getY() > y && entry->getY() + _guiStyle.dimensions.Y < y) {
			
			return entry;
		}
	}
	return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
// Event methods
///////////////////////////////////////////////////////////////////////////////

void GuiComponent::resize(Vector2 newSize) {
	// Views use a ratio of 0.0 to 1.0 to determine how much of the screen
	// to use. Since we provide the position and size in pixels, we convert them
	float origin_x = _pos.X / newSize.X;
	float origin_y = _pos.Y / newSize.Y;
	float r_width = _size.X / newSize.X;
	float r_height = _size.Y / newSize.Y;
	_view.setViewport(sf::FloatRect(origin_x, origin_y, r_width, r_height));
}
