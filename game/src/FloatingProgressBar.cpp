#include "game/FloatingProgressBar.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

FloatingProgressBar::FloatingProgressBar(Vector2 size,
		sf::Color backgroundColor, sf::Color valueColor,
		float min, float max, float cur)
	: _maxValue(max), _curValue(cur), _minValue(min) {

	_backgroundBar.setSize(sf::Vector2f(size.X, size.Y));
	_backgroundBar.setFillColor(backgroundColor);
	_backgroundBar.setOutlineColor(sf::Color::Black);
	_backgroundBar.setOutlineThickness(-1.0f);

	_valueBar.setSize(sf::Vector2f(size.X, size.Y));
	_valueBar.setFillColor(valueColor);
	_valueBar.setOutlineColor(sf::Color::Black);
	_valueBar.setOutlineThickness(-1.0f);
}

FloatingProgressBar::~FloatingProgressBar() {}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Updating
////////////////////////////////////////////////////////////////////////////////

void FloatingProgressBar::draw(sf::RenderTarget& target,
		sf::RenderStates state) const {

	target.draw(_backgroundBar);
	target.draw(_valueBar);
}

void FloatingProgressBar::update(int diff) {

}

void FloatingProgressBar::updateBar() {
	_valueBar.setSize(sf::Vector2f(getWidth() * getRatioFull(), getHeight()));
}

////////////////////////////////////////////////////////////////////////////////
// Position methods
////////////////////////////////////////////////////////////////////////////////

void FloatingProgressBar::setPosition(float x, float y) {
	_valueBar.setPosition(x, y);
	_backgroundBar.setPosition(x, y);
}

////////////////////////////////////////////////////////////////////////////////
// Setters
////////////////////////////////////////////////////////////////////////////////

void FloatingProgressBar::setMaxValue(float f) {
	_maxValue = f;
	updateBar();
}

void FloatingProgressBar::setCurrentValue(float f) {
	_curValue = f;
	updateBar();
}

void FloatingProgressBar::setMinValue(float f) {
	_minValue = f;
	updateBar();
}

////////////////////////////////////////////////////////////////////////////////
// Size methods
////////////////////////////////////////////////////////////////////////////////

float FloatingProgressBar::getWidth() {
	return _backgroundBar.getSize().x;
}

float FloatingProgressBar::getHeight() {
	return _backgroundBar.getSize().y;
}
