#include "game/gui/GuiProgressBar.h"

#include "game/gui/GuiComponent.h"
#include "game/util/ColorUtil.h"

#include "logger/Logger.h"

#include "util/UtilString.h"
#include "util/UtilMath.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GuiProgressBar::GuiProgressBar(GuiComponent* guiComp,
		const std::string& msg, const GuiProgressBarStyle* barStyle,
		float* value, float min, float* max)
	: GuiEntry(guiComp, msg),
		_barStyle(barStyle), _value(value), _prevValue(-1),
		_min(min), _max(max), _prevMax(-1) {

	_bar.setSize(sf::Vector2f(_style->getDimensions().X,
		_style->getDimensions().Y));	
	_bar.setFillColor(barStyle->getMaxColor());

	_barOutline.setFillColor(sf::Color::Transparent);
	_barOutline.setOutlineThickness(-1.0f);
	_barOutline.setOutlineColor(barStyle->getOutlineColor());
	_barOutline.setSize(_bar.getSize());

	_barBackground.setFillColor(barStyle->getBackgroundColor());
	_barBackground.setSize(_bar.getSize());

	// Set up all the texts used in a bar
	_zeroText.setFont(*_text.getFont());
	_zeroText.setFillColor(barStyle->getMinColor());
	_zeroText.setOutlineThickness(1.0f);
	_zeroText.setOutlineColor(sf::Color::Black);
	_zeroText.setString(ag::String::format("%g", _min));
	_zeroText.setCharacterSize(_text.getCharacterSize());

	_currentText.setFont(*_text.getFont());
	_currentText.setFillColor(sf::Color::White);
	_currentText.setOutlineThickness(1.0f);
	_currentText.setOutlineColor(sf::Color::Black);
	_currentText.setCharacterSize(_text.getCharacterSize());

	if (_value == nullptr) {
		_currentText.setString("0");
	} else {
		_currentText.setString(ag::String::toString(getCurrentValue()));
	}

	_maxText.setFont(*_text.getFont());
	_maxText.setFillColor(barStyle->getMaxColor());
	_maxText.setOutlineThickness(1.0f);
	_maxText.setOutlineColor(sf::Color::Black);
	_maxText.setCharacterSize(_text.getCharacterSize());

	if (_max == nullptr) {
		_maxText.setString("0");
	} else {
		_maxText.setString(ag::String::toString(getMax()));
	}
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
		updateBar();
		_prevValue = getCurrentValue();
	}

	if (_prevMax != getMax()) {
		updateBar();
		_prevMax = getMax();
	}
}

void GuiProgressBar::updateBar() {
	_bar.setFillColor(ColorUtil::colorInterpolate(
		_barStyle->getMinColor(), _barStyle->getMaxColor(), getRatioDone()));

	_currentText.setString(ag::String::toString(getCurrentValue()));
	_maxText.setString(ag::String::toString(getMax()));

	_currentText.setPosition(getX() + (_style->getDimensions().X / 2.0f)
		- _currentText.getLocalBounds().width / 2.0f, getY());
	_maxText.setPosition(getX() + _style->getDimensions().X
		- (_maxText.getLocalBounds().width + 4.0f), getY());

	_bar.setSize(sf::Vector2f(_style->getDimensions().X * getRatioDone(),
		_style->getDimensions().Y));
}

void GuiProgressBar::setMin(float m) {
	_min = m;
	_zeroText.setString(ag::String::format("%g", _min));
}
	
void GuiProgressBar::setMax(float m) {
	*_max = m;
	_maxText.setString(ag::String::format("%g", getMax()));
}

void GuiProgressBar::setPosition(float x, float y) {
	GuiEntry::setPosition(x, y);

	_bar.setPosition(getX(), getY());
	_barOutline.setPosition(getX(), getY());
	_barBackground.setPosition(getX(), getY());

	_zeroText.setPosition(getX(), getY());

	// Move the text back so it doesn't go off the screen
	_currentText.setPosition(getX() + (_style->getDimensions().X / 2.0f)
		- _currentText.getLocalBounds().width / 2.0f, getY());
	_maxText.setPosition(getX() + _style->getDimensions().X
		- (_maxText.getLocalBounds().width + 4.0f), getY());
}
