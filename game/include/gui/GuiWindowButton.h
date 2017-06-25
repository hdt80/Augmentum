#pragma once

#include "game/gui/GuiButton.h"
#include "game/gui/GuiComponent.h"

// When clicked a GuiWindowButton will lead the game to a new Window
class GuiWindowButton : public GuiButton {
public:	
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// Ctor for GuiMenuButton
	// style - Style to draw the GuiWindowButton as
	// origin - Where to draw the GuiWindowButton from
	// msg - Message to display on the button
	// window - Window to follow when the GuiWindowButton is pressed
	GuiWindowButton(GuiComponent* guiComp,
		const std::string& msg, Window* window);

	// Dtor for GuiWindowButton
	virtual ~GuiWindowButton();

	// Methods /////////////////////////////////////////////////////////////////

	virtual void onClick();

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	Window* _window; // Window to follow when this is pressed
};
