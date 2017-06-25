#include "game/gui/GuiComponent.h"

#include "game/gui/GuiButton.h"
#include "game/Window.h"
#include "game/Game.h"
#include "game/util/StringUtil.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GuiComponent::GuiComponent(Window* window, const GuiEntryStyle* style,
		const GuiComponentStyle* compStyle, Vector2 pos, Vector2 size)
	: _pos(pos), _size(size),
		_guiEntryStyle(style), _highlightedEntry(nullptr),
		_visible(true), _updating(true), _clickable(true),
		_window(window) {

	// Components start at (0, 0) and not the position because a view represents
	// a view to a part of a drawing target, and we're drawn to (0, 0)
	_view.reset(sf::FloatRect(0, 0, size.X, size.Y));

	resize(window->getSize());

	_background.setSize(sf::Vector2f(_size.X, _size.Y));
	_background.setPosition(0, 0);
	_background.setFillColor(compStyle->getBodyColor());
	_background.setOutlineColor(compStyle->getBorderColor());
	_background.setOutlineThickness(-compStyle->getBorderSize());
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
	for (GuiEntry* entry : _entries) {
		entry->update(diff);
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(Game::getRenderWindow());	
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

	target.draw(_background);

	for (GuiEntry* entry : _entries) {
		target.draw(*entry);
	}
}

////////////////////////////////////////////////////////////////////////////////
// Bounds methods
////////////////////////////////////////////////////////////////////////////////

bool GuiComponent::contains(float x, float y) const {
	return (x >= _pos.X && x <= _size.X + _pos.X &&
		y >= _pos.Y && y <= _size.Y + _pos.Y);
}

bool GuiComponent::hasClicked(float x, float y) const {
	if (!_clickable) {
		return false;
	}
	return contains(x, y);
}	

void GuiComponent::addEntry(GuiEntry* entry, float x, float y) {
	entry->setPosition(x, y);
	_entries.push_back(entry);
}

GuiEntry* GuiComponent::getEntry(float x, float y) const {
	for (unsigned int i = 0; i < _entries.size(); ++i) {
		if (_entries[i]->contains(x, y)) {
			return _entries[i];
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

void GuiComponent::onClick(int button, float window_x, float window_y,
		float view_x, float view_y) {
	
	if (!isClickable()) {
		return;
	}
	
	GuiEntry* clicked = getEntry(window_x, window_y);

	if (!clicked) {
		return;
	}

	GuiButton* guiButton = dynamic_cast<GuiButton*>(clicked);

	if (guiButton) {
		guiButton->onClick();
	}
}
