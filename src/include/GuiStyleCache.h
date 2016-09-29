#ifndef _GUI_STYLE_CACHE_H
#define _GUI_STYLE_CACHE_H

#include <string>
#include "GuiComponent.h"

class GuiStyleCache {
public:
	// Store a GuiStyle under a name into the cache
	// name - Name to store the GuiStyle as
	// style - Style to save 
	static void saveStyle(const std::string& name, GuiEntryStyle* style);

	// Get a saved GuiStyle
	// name - Name the the GuiStyle was stored under
	static const GuiEntryStyle* getStyle(const std::string& name);

	// Check if a GuiStyle is saved in this cache
	// name - Name of the font to check
	static bool contains(const std::string& name);

private:
	static std::map<std::string, GuiEntryStyle*> _styleCache;
};

#endif
