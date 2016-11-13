#ifndef _GUI_PROGRESS_BAR_H
#define _GUI_PROGRESS_BAR_H

#include "GuiEntry.h"
#include "Logger.h"

struct GuiProgressBarStyle {
	sf::Color minColor; // Color to draw the bar when value = 0
	sf::Color maxColor; // Color to draw the bar when value = 100
	sf::Color outlineColor; // Color of the outline around the bar
	sf::Color backgroundColor; // Color to fill when the bar isn't full

	bool vert; // If the bar should be up/down  TODO: Add this
};

class GuiProgressBar : public GuiEntry {
public:
	// GuiProgressBar ctor
	// style - Style to draw this GuiEntry
	// origin - Origin of the GuiComponent this GuiEntry is in
	// msg - Message to display
	// barStyle - How to style the bar
	// value - Pointer to the value to track
	// min - Min value that value can be
	// max - Pointer to the max value that value can be
	GuiProgressBar(const GuiEntryStyle* style, Vector2 origin,
			const std::string& msg,	GuiProgressBarStyle* barStyle,
			float* value, float min, float* max);
	virtual ~GuiProgressBar();

	// Inherited from sf::Drawable
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	// Update this GuiEntry
	// diff - Microseconds since the last update
	virtual void update(int diff);

	// Set the position of the GuiEntry
	// x - X coord relative to the GuiComponent's origin
	// y - Y coord relative to the GuiComponent's origin
	virtual void setPosition(float x, float y);

	// Get the current value used by this bar
	// returns: What the current value is
	virtual inline float getCurrentValue() { return *_value; }

	// Get how much higher the value is from the min value
	// returns: Remainder of value till max is hit
	virtual inline float getRelativeValue() { return getCurrentValue() - _min; }

	// Get how close the value is to the max
	// returns: A ratio of how "done" the value is (0: 0%, 1: 100%)
	inline float getRatioDone() { return getRelativeValue()
			/ getRelativeMax(); }

	// Get the ratio of how far from the value is to the max
	// returns: A ration of how much of the value is needed to hit the max
	inline float getRatioLeft() { return 1.0f - getRatioDone(); }

	// Get the maximum value of this bar
	// returns: The max value _value can be before it's considered "done"
	virtual inline float getMax() { return *_max; }

	// Get how much higher the max is from the min
	// returns: How higher the max is from the min
	virtual inline float getRelativeMax() { return getMax() - _min; }

	// Set the max value of this bar
	// m - New mav value to use
	void setMax(float m);

	// Set the min value of this bar
	// m - New min value to use
	void setMin(float m);

protected:

	// Update the progress bar based on the current values
	void updateBar();

	GuiProgressBarStyle* _barStyle;

	sf::RectangleShape _bar; // Bar to draw, colored portion
	sf::RectangleShape _barOutline; // Outline of the bar
	sf::RectangleShape _barBackground; // Background of the bar
	sf::Text _zeroText; // Text to draw at the min value
	sf::Text _currentText; // Text to draw the current values
	sf::Text _maxText; // Text to draw at the max value

	float* _value; // Pointer to the value
	float _prevValue; // Previous value, used to check if the bar needs updating
	float _min; // Min value of the tracked valued
	float* _max; // Max value of this

	float _prevMax; // Previous max, used to check if the bar needs updating
};

#endif
