#include "GuiProgressBar.h"
#include "GuiComponent.h"
#include "Convert.h"
#include "Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GuiProgressBar::GuiProgressBar(const GuiEntryStyle* style, Vector2 origin,
		const std::string& msg, GuiProgressBarStyle* barStyle,
		float* value, float min, float max)
	: GuiEntry(style, origin, msg),
		_barStyle(barStyle), _value(value), _prevValue(-1),
		_min(min), _max(max) {

	_bar.setSize(sf::Vector2f(style->dimensions.X, style->dimensions.Y));	
	_bar.setFillColor(barStyle->maxColor);

	_barOutline.setFillColor(sf::Color::Transparent);
	_barOutline.setOutlineThickness(-1.0f);
	_barOutline.setOutlineColor(barStyle->outlineColor);
	_barOutline.setSize(_bar.getSize());

	_barBackground.setFillColor(barStyle->backgroundColor);
	_barBackground.setSize(_bar.getSize());

	// Set up all the texts used in a bar
	_zeroText.setFont(*_text.getFont());
	_zeroText.setFillColor(barStyle->minColor);
	_zeroText.setOutlineThickness(1.0f);
	_zeroText.setOutlineColor(sf::Color::Black);
	_zeroText.setString(convert::format("%g", _min));
	_zeroText.setCharacterSize(_text.getCharacterSize());

	_currentText.setFont(*_text.getFont());
	_currentText.setFillColor(sf::Color::White);
	_currentText.setOutlineThickness(1.0f);
	_currentText.setOutlineColor(sf::Color::Black);
	_currentText.setCharacterSize(_text.getCharacterSize());

	if (_value == nullptr) {
		_currentText.setString("0");
	} else {
		_currentText.setString(convert::toString(getCurrentValue()));
	}

	_maxText.setFont(*_text.getFont());
	_maxText.setFillColor(barStyle->maxColor);
	_maxText.setOutlineThickness(1.0f);
	_maxText.setOutlineColor(sf::Color::Black);
	_maxText.setString(convert::toString(_max));
	_maxText.setCharacterSize(_text.getCharacterSize());
}

GuiProgressBar::~GuiProgressBar() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void GuiProgressBar::draw(sf::RenderTarget& target,
		sf::RenderStates states) const {

	target.draw(_barBackground);
	target.draw(_bar);
	target.draw(_barOutline);
	target.draw(_zeroText);
	target.draw(_currentText);
	target.draw(_maxText);
}

void GuiProgressBar::update(int diff) {
	// Only update the progress bar if the value has changed
	if (getCurrentValue() != _prevValue) {
		_bar.setFillColor(convert::colorInterpolate(
				_barStyle->minColor, _barStyle->maxColor, getRatioDone()));

		_currentText.setString(convert::toString(getCurrentValue()));

		_bar.setSize(sf::Vector2f(_style->dimensions.X * getRatioDone(),
				_style->dimensions.Y));

		_prevValue = getCurrentValue();
	}
}

void GuiProgressBar::setMin(float m) {
	_min = m;
	_zeroText.setString(convert::format("%g", _min));
}
	
void GuiProgressBar::setMax(float m) {
	_max = m;
	_maxText.setString(convert::format("%g", _max));
}

void GuiProgressBar::setPosition(float x, float y) {
	GuiEntry::setPosition(x, y);

	_bar.setPosition(getX(), getY());
	_barOutline.setPosition(getX(), getY());
	_barBackground.setPosition(getX(), getY());

	_zeroText.setPosition(getX(), getY());

	// Move the text back so it doesn't go off the screen
	_currentText.setPosition(getX() + (_style->dimensions.X / 2.0f)
			- _currentText.getLocalBounds().width / 2.0f, getY());
	_maxText.setPosition(getX() + _style->dimensions.X
			- (_maxText.getLocalBounds().width + 4.0f), getY());
}
