#ifndef _GUI_BUTTON_H
#define _GUI_BUTTON_H

#include "GuiEntry.h"

class GuiButton : public GuiEntry {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// GuiButton ctor
	// guiComp - GuiComponent the GuiButton is in
	// msg - Text to display on the button
	GuiButton(GuiComponent* guiComp, const std::string& msg);

	// GuiButton dtor
	virtual ~GuiButton();

	// Methods /////////////////////////////////////////////////////////////////

	// What should occurs when the GuiButton is clicked?
	virtual void onClick() {};
};

#endif
