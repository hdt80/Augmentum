#ifndef _GUI_EXP_PROGRESS_BAR_H
#define _GUI_EXP_PROGRESS_BAR_H

#include "gui/GuiProgressBar.h"
#include "Unit.h"

class GuiExpProgressBar : public GuiProgressBar {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Unique GuiProgressBar for an exp bar
	// guiComp - GuiComponent the GuiExpProgressBar is in
	// msg - Message to display
	// barStyle - Style to draw this GuiProgressBar
	// unit - Unit to track to exp of
	GuiExpProgressBar(GuiComponent* guiComp, const std::string& msg,
		const GuiProgressBarStyle* barStyle, Unit* unit);

	// GuiExpProgressBar progress bar
	virtual ~GuiExpProgressBar() {}

	// Methods /////////////////////////////////////////////////////////////////

	// Update this GuiEntry
	// diff - Microseconds to update
	virtual void update(int diff);

	// Get how much exp the unit currently has
	// returns: How much exp the unit has
	virtual float getCurrentValue();

	// Get the max (Exp needed to reach the next level)
	// returns: The exp required to hit the next level
	virtual float getMax() const;

	// Get the min exp needed to reach the current level
	// returns: exp needed to reach the unit's current level
	virtual float getMin() const;

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	Unit* _tracked; // Selected ship
	int _prevLevel; // Previous level of the tracked unit
	float _prevMax; // Previous exp needed to reach the next level
};

#endif
