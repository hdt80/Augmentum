#include "GuiExpProgressBar.h"

#include "ExperienceHelper.h"

#include "util/StringUtil.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////
GuiExpProgressBar::GuiExpProgressBar(const GuiEntryStyle* style, Vector2 origin,
		const std::string& msg, GuiProgressBarStyle* barStyle, Unit* unit)
	: GuiProgressBar(style, origin, msg, barStyle, nullptr, 0, 0),
		_tracked(unit) {

	if (_max == nullptr) {
		_max = new float;
	}
	
	_value = &_tracked->getExp();
	_prevLevel = 0;

	_zeroText.setString("0");
	_currentText.setString(StringUtil::format("%g", _tracked->getExp()));
	_maxText.setString(StringUtil::format("%g", getMax()));
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void GuiExpProgressBar::update(int diff) {
	if (_prevValue != getCurrentValue()) {
		_min = getMin();
		setMax(getMax());
		_zeroText.setString(StringUtil::format("%g", getMin()));
		_maxText.setString(StringUtil::format("%g", getMax()));
		setPosition(getX(), getY()); // Reposition the texts
	}
	GuiProgressBar::update(diff);
}

float GuiExpProgressBar::getCurrentValue() {
	return _tracked->getExp();
}

float GuiExpProgressBar::getMin() {
	return ExperienceHelper::levelToExp(_tracked->getLevel());
}

float GuiExpProgressBar::getMax() {
	return ExperienceHelper::levelToExp(_tracked->getLevel() + 1);
}
