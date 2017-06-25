#pragma once

#include "game/gui/GuiButton.h"
#include "game/gui/GuiComponent.h"

// When clicked a GuiMenuButton will change the opened menu
class GuiMenuButton : public GuiButton {
public:	
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// GuiMenuButton ctor
	// guiComp - GuiComponent that has the GuiMenuButton
	// msg - Message to draw on the button
	// comp - GuiComponent toggled visibility when the GuiMenuButton is clicked
	GuiMenuButton(GuiComponent* guiComp,
			const std::string& msg, GuiComponent* comp);

	// GuiMenuButton dtor
	virtual ~GuiMenuButton();

	// Methods /////////////////////////////////////////////////////////////////

	// Occurs when the GuiMenuButton is clicked
	virtual void onClick();

protected:
	GuiComponent* _guiComp; // Component to toggle visibility
};
