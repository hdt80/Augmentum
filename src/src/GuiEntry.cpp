#include "GuiEntry.h"
#include "GuiComponent.h"

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////
GuiEntry::GuiEntry() {}

GuiEntry::GuiEntry(GuiStyle* style, const std::string& msg) {
	_shape.setSize(sf::Vector2f(style->dimensions.X, style->dimensions.Y));	
	_shape.setFillColor(style->bodyColor);
	_shape.setOutlineColor(style->borderColor);
	// Negative so the border goes in
	_shape.setOutlineThickness(-style->borderSize);

	_text.setFont(*style->font);
	_text.setString(msg);
	_text.setFillColor(style->textColor);
	_text.setOutlineColor(sf::Color::Black);
	_text.setOutlineThickness(-1.0f);
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
