#include "GuiProgressBar.h"
#include "GuiComponent.h"

GuiProgressBar::GuiProgressBar(const GuiEntryStyle* style, Vector2 origin,
		const std::string& msg, GuiProgressBarStyle* barStyle,
		float* value, float max)
	: GuiEntry(style, origin, msg),
		_value(value), _max(max) {

	_bar.setSize(sf::Vector2f(style->dimensions.X, style->dimensions.Y));	
	_bar.setFillColor(barStyle->maxColor);
}

GuiProgressBar::~GuiProgressBar() {

}
