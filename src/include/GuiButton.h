#ifndef _GUI_BUTTON_H
#define _GUI_BUTTON_H

#include "GuiEntry.h"

class GuiButton : public GuiEntry {
public:
	GuiButton(GuiEntryStyle* style, const std::string& msg);
	virtual ~GuiButton();

	virtual void onClick() {};
};

#endif
