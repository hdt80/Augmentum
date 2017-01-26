#include "gui/GuiWindowButton.h"

#include "Game.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GuiWindowButton::GuiWindowButton(GuiComponent* guiComp,
		const std::string& msg, Window* window)
	: GuiButton(guiComp, msg),
		_window(window) {

}

GuiWindowButton::~GuiWindowButton() {
	_window = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void GuiWindowButton::onClick() {
	Game::followWindow(_window);
}
