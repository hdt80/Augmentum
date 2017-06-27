#include "game/gui/GuiExpProgressBar.h"

#include "game/ExperienceHelper.h"

#include "util/UtilString.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////
GuiExpProgressBar::GuiExpProgressBar(GuiComponent* guiComp,
		const std::string& msg, const GuiProgressBarStyle* barStyle, Unit* unit)
	: GuiProgressBar(guiComp, msg, barStyle, nullptr, 0, 0),
		_tracked(unit) {

	if (_max == nullptr) {
		_max = new float;
	}
	
	_value = &_tracked->getExp();
	_prevLevel = 0;

	_zeroText.setString("0");
	_currentText.setString(ag::String::format("%g", _tracked->getExp()));
	_maxText.setString(ag::String::format("%g", getMax()));
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void GuiExpProgressBar::update(int diff) {
	if (_prevValue != getCurrentValue()) {
		_min = getMin();
		setMax(getMax());
		_zeroText.setString(ag::String::format("%g", getMin()));
		_maxText.setString(ag::String::format("%g", getMax()));
		setPosition(getX(), getY()); // Reposition the texts
	}
	GuiProgressBar::update(diff);
}

float GuiExpProgressBar::getCurrentValue() {
	return _tracked->getExp();
}

float GuiExpProgressBar::getMin() const {
	return ExperienceHelper::levelToExp(_tracked->getLevel());
}

float GuiExpProgressBar::getMax() const {
	return ExperienceHelper::levelToExp(_tracked->getLevel() + 1);
}
