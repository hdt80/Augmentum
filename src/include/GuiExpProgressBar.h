#ifndef _GUI_EXP_PROGRESS_BAR_H_
#define _GUI_EXP_PROGRESS_BAR_H_

#include "GuiProgressBar.h"
#include "Unit.h"

class GuiExpProgressBar : public GuiProgressBar {
public:
	// Unique GuiProgressBar for an exp bar
	// style - Style draw this GuiExpProgressBar
	// origin - Origin of the GuiComponent this GuiExpProgressBar is in
	// msg - Message to display
	// barStyle - Style to draw this GuiProgressBar
	// unit - Unit to track to exp of
	GuiExpProgressBar(const GuiEntryStyle* style, Vector2 origin,
			const std::string& msg,	GuiProgressBarStyle* barStyle, Unit* unit);
	virtual ~GuiExpProgressBar() {}

	// Update this GuiEntry
	// diff - Microseconds to update
	virtual void update(int diff);

	// Get how much exp the unit currently has
	// returns: How much exp the unit has
	virtual float getCurrentValue();

	// Get the max (Exp needed to reach the next level)
	// returns: The exp required to hit the next level
	virtual float getMax();

	// Get the min exp needed to reach the current level
	// returns: exp needed to reach the unit's current level
	virtual float getMin();

protected:
	Unit* _tracked; // Selected ship
	int _prevLevel; // Previous level of the tracked unit
	float _prevMax; // Previous exp needed to reach the next level
};

#endif
