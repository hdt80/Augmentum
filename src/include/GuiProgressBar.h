#ifndef _GUI_PROGRESS_BAR_H
#define _GUI_PROGRESS_BAR_H

#include "GuiEntry.h"

struct GuiProgressBarStyle {
	sf::Color minColor; // Color to draw the bar when value = 0
	sf::Color maxColor; // Color to draw the bar when value = 100

	bool vert; // If the bar should be up/down 
};

class GuiProgressBar : public GuiEntry {
public:
	GuiProgressBar(const GuiEntryStyle* style, Vector2 origin,
			const std::string& msg,	GuiProgressBarStyle* barStyle,
			float* value, float max);
	~GuiProgressBar();

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
	inline float getCurrentValue() { return *_value; }

	// Get how close the value is to the max
	// returns: A ratio of how "done" the value is (0: 0%, 1: 100%)
	inline float getRatioDone() { return getCurrentValue() / _max; }

	// Get the maximum value of this bar
	// returns: The max value _value can be before it's considered "done"
	inline float getMax() { return _max; }

	// Set the max value of this bar
	// m - New mav value to use
	void setMax(float m);

protected:
	GuiProgressBarStyle* _barStyle;

	sf::RectangleShape _bar;
	sf::Text _zeroText; // Text to draw at the min value
	sf::Text _currentText; // Text to draw the current values
	sf::Text _maxText; // Text to draw at the max value

	float* _value; // Pointer to the value
	float _max; // Max value of this, min is assumed to be 0
};

#endif
