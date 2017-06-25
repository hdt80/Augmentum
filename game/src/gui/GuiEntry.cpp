#include "game/gui/GuiEntry.h"

#include "game/gui/GuiComponent.h"
#include "game/gui/GuiComponent.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

GuiEntry::GuiEntry(GuiComponent* guiComp, const std::string& msg) {
	_comp = guiComp;
	_style = guiComp->getEntryStyle();
	_origin = guiComp->getPos();

	// Set up the background shape
	_shape.setSize(sf::Vector2f(_style->getDimensions().X,
		_style->getDimensions().Y));	
	_shape.setFillColor(_style->getBodyColor());
	_shape.setOutlineColor(_style->getBorderColor());
	// Negative so the border goes in
	_shape.setOutlineThickness(-_style->getBorderSize());

	_text.setFont(*_style->getFont());
	_text.setString(msg);
	_text.setFillColor(_style->getTextColor());
	_text.setOutlineColor(sf::Color::Black);
	_text.setOutlineThickness(1.0f);
	setMessage(msg);
	
	// Find the font size programmically?
	if (_style->getTextSize() < 0) {
		// Determine how big each character should be
		_text.setCharacterSize(_style->getDimensions().Y
				- _style->getBorderSize() - _style->getPadding());
	} else {
		// TODO: Factor in padding
		_text.setCharacterSize(_style->getTextSize());
	}

	_highlighted = false;
}

GuiEntry::~GuiEntry() {}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void GuiEntry::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_shape);
	target.draw(_text);
}

void GuiEntry::setMessage(const std::string& msg) {
	_msg = msg;
	_text.setString(_msg);
}

void GuiEntry::setPosition(float x, float y) {
	_shape.setPosition(x, y);
	_text.setPosition(x, y);
}

void GuiEntry::setHighlighted(bool b) {
	_highlighted = b;
	if (_highlighted) {
		_shape.setFillColor(_style->getHighlightedColor());
		_shape.setOutlineColor(_style->getHighlightedBorderColor());
		_text.setFillColor(_style->getHighlightedTextColor());
	} else {
		_shape.setFillColor(_style->getBodyColor());
		_shape.setOutlineColor(_style->getBorderColor());
		_text.setFillColor(_style->getTextColor());
	}
}

bool GuiEntry::contains(float x, float y) const {
	return (x >= getX() && x <= _style->getDimensions().X + getX() &&
		y >= getY() && y <= _style->getDimensions().Y + getY());
}
