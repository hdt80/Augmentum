#include "game/gui/GuiMenuButton.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GuiMenuButton::GuiMenuButton(GuiComponent* guiComp,
		const std::string& msg,	GuiComponent* comp)
	: GuiButton(guiComp, msg),
		_guiComp(comp) {

}

GuiMenuButton::~GuiMenuButton() {

}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void GuiMenuButton::onClick() {
	// Use the same variable to ensure that it's the same value
	_guiComp->setClickable(!_guiComp->isVisible());
	_guiComp->setVisible(!_guiComp->isVisible());
}