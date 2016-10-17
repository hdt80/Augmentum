#include "GuiExpProgressBar.h"

#include "ExperienceHelper.h"
#include "Convert.h"
////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////
GuiExpProgressBar::GuiExpProgressBar(const GuiEntryStyle* style, Vector2 origin,
		const std::string& msg, GuiProgressBarStyle* barStyle, Unit* unit)
	: GuiProgressBar(style, origin, msg, barStyle, nullptr, 0),
		_tracked(unit) {
	
	_value = &_tracked->getExp();

	_currentText.setString(convert::format("%g", _tracked->getExp()));
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void GuiExpProgressBar::update(int diff) {
	if (getMax() != _prevMax) {
		_maxText.setString(convert::format("%g", getMax()));
		_prevMax = getMax();
	}
	GuiProgressBar::update(diff);
}

float GuiExpProgressBar::getCurrentValue() {
	return _tracked->getExp();
}

float GuiExpProgressBar::getMax() {
	return ExperienceHelper::levelToExp(_tracked->getLevel() + 1);
}
