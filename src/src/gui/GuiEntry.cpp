#include "gui/GuiEntry.h"

#include "Logger.h"

#include "gui/GuiComponent.h"
#include "gui/GuiComponent.h"

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

GuiEntry::GuiEntry(GuiComponent* guiComp, const std::string& msg) {
	_comp = guiComp;
	_style = guiComp->getEntryStyle();
	_origin = guiComp->getPos();

	// Set up the background shape
	_shape.setSize(sf::Vector2f(_style->dimensions.X, _style->dimensions.Y));	
	_shape.setFillColor(_style->bodyColor);
	_shape.setOutlineColor(_style->borderColor);
	// Negative so the border goes in
	_shape.setOutlineThickness(-_style->borderSize);

	_text.setFont(*_style->font);
	_text.setString(msg);
	_text.setFillColor(_style->textColor);
	_text.setOutlineColor(sf::Color::Black);
	_text.setOutlineThickness(1.0f);
	setMessage(msg);
	
	// Find the font size programmically?
	if (_style->textSize < 0) {
		// Determine how big each character should be
		_text.setCharacterSize(_style->dimensions.Y
				- _style->borderSize - _style->padding);
	} else {
		// TODO: Factor in padding
		_text.setCharacterSize(_style->textSize);
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
		_shape.setFillColor(_style->highlightedColor);
		_shape.setOutlineColor(_style->highlightedBorderColor);
		_text.setFillColor(_style->highlightedTextColor);
	} else {
		_shape.setFillColor(_style->bodyColor);
		_shape.setOutlineColor(_style->borderColor);
		_text.setFillColor(_style->textColor);
	}
}

bool GuiEntry::contains(float x, float y) const {
	return (x >= getX() && x <= _style->dimensions.X + getX() &&
		y >= getY() && y <= _style->dimensions.Y + getY());
}
