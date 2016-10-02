#include "GuiEntry.h"
#include "GuiComponent.h"
#include "Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

GuiEntry::GuiEntry(const GuiEntryStyle* style,
		Vector2 orig, const std::string& msg) {

	_style = style;
	_origin = orig;
	_shape.setSize(sf::Vector2f(style->dimensions.X, style->dimensions.Y));	
	_shape.setFillColor(style->bodyColor);
	_shape.setOutlineColor(style->borderColor);
	// Negative so the border goes in
	_shape.setOutlineThickness(-style->borderSize);

	_text.setFont(*style->font);
	_text.setString(msg);
	_text.setFillColor(style->textColor);
	_text.setOutlineColor(sf::Color::Black);
	_text.setOutlineThickness(1.0f);
	setMessage(msg);
	
	// Find the font size programmically?
	if (style->textSize < 0) {
		// Determine how big each character should be
		_text.setCharacterSize(style->dimensions.Y
				- style->borderSize - style->padding);
	} else {
		// TODO: Factor in padding
		_text.setCharacterSize(style->textSize);
	}

	_highlighted = false;
}

GuiEntry::~GuiEntry() {}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

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

bool GuiEntry::contains(float x, float y) {
	//CORE_INFO("Checking (%g, %g) againist (%g, %g)", x, y, getX(), getY());
	return (x >= getX() && x <= _style->dimensions.X + getX() &&
			y >= getY() && y <= _style->dimensions.Y + getY());
}
