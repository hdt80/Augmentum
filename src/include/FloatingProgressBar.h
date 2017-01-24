#ifndef _FLOATING_PROGRESS_BAR_H
#define _FLOATING_PROGRESS_BAR_H

#include <SFML/Graphics.hpp>

#include "Vector2.h"

class FloatingProgressBar : public sf::Drawable {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// FloatingProgressBar ctor
	// backgroundColor - Color to draw the background bar
	// valueColor - Color to draw the value bar
	// min - Min value to use
	// max - Max value to use
	// cur - Current value to use
	FloatingProgressBar(Vector2 size, sf::Color backgroundColor,
			sf::Color valueColor, float min, float max, float cur);

	// FloatingProgressBar dtor
	~FloatingProgressBar();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Update methods //////////////////////////////////////////////////////////

	// Simulate the FloatingProgressBar for an amount of time
	// diff - Microseconds to simulate for
	void update(int diff);
	
	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	// Position methods ////////////////////////////////////////////////////////
	
	// Get the x position of this bar
	// returns: The x pos of _valueBar
	float getX() const { return _valueBar.getPosition().y; }

	// Get the y position of this bar
	// returns: The y pos of _valueBar
	float getY() const { return _valueBar.getPosition().x; }

	// Set the position of this bar
	// x - X coord to set
	// y - Y coord to set
	void setPosition(float x, float y);

	// Size methods ////////////////////////////////////////////////////////////

	// Get the width of this bar
	// returns: the width of _backgroundBar
	float getWidth();

	// Get the height of this bar
	// returns: the height of _backgroundBar
	float getHeight();

	// Getters /////////////////////////////////////////////////////////////////
	
	// Get the value that will draw the bar as full
	// returns: _maxValue
	inline float getMaxValue() const { return _maxValue; }

	// Get the current value of this bar
	// returns: _curValue
	inline float getCurrentValue() const { return _curValue; }

	// Get the min value that will draw the bar as empty
	// returns: _minValue
	inline float getMinValue() const { return _minValue; }

	// Get how full the FloatingProgressBar is
	// returns: _curValue / _maxValue
	inline float getRatioFull() const {
		return getCurrentValue() / getMaxValue(); }

	// Setters /////////////////////////////////////////////////////////////////
	
	// Set the max value of this bar
	// f - Max value to set
	void setMaxValue(float f);

	// Set the current value of this bar
	// f - Current value to set
	void setCurrentValue(float f);

	// Set the min value of this bar
	// f - Min value to set
	void setMinValue(float f);

protected:
	
	// Update the _valueBar to match the values
	void updateBar();

	sf::RectangleShape _backgroundBar; // Shape to draw the background
	sf::RectangleShape _valueBar; // Shape to draw the current value

	float _maxValue; // Max value of thie bar
	float _curValue; // Current value of this bar
	float _minValue; // Min value of this bar
};

#endif
