#ifndef _GUI_MENU_BUTTON_H
#define _GUI_MENU_BUTTON_H

#include "GuiButton.h"
#include "GuiComponent.h"

// When clicked a GuiMenuButton will change the opened menu
class GuiMenuButton : public GuiButton {
public:	
	GuiMenuButton(GuiEntryStyle* style,
			const std::string& msg, GuiComponent* comp);
	virtual ~GuiMenuButton();

	virtual void onClick();

protected:
	GuiComponent* _guiComp; // Component to toggle visibility
};

#endif
