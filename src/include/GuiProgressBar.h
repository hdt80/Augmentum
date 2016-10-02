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

	// Get the current value used by this bar
	// returns: What the current value is
	inline float getCurrentValue() { return *_value; }

	// Get how close the value is to the max
	// returns: A ratio of how "done" the value is (0: 0%, 1: 100%)
	inline float getRatioDone() { return getCurrentValue() / _max; }

protected:
	sf::RectangleShape _bar;
	sf::Text _zeroText; // Text to draw at the min value
	sf::Text _currentText; // Text to draw the current values
	sf::Text _maxText; // Text to draw at the max value

	float* _value; // Pointer to the value
	float _max; // Max value of this, min is assumed to be 0
};

#endif
