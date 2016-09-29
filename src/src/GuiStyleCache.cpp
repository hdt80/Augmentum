#include "GuiStyleCache.h"
#include "Logger.h"

void GuiStyleCache::saveStyle(const std::string& name, GuiEntryStyle* style) {
	if (contains(name)) {
		CORE_WARN("Overwriting a saved GuiStyle: \'%s\'", name.c_str());
	}
	_styleCache[name] = style;
}

const GuiEntryStyle* GuiStyleCache::getStyle(const std::string& name) {
	if (!contains(name)) {
		CORE_WARN("Could not load \'%s\'. Not loaded!", name.c_str());
		return nullptr;
	}
	return _styleCache.at(name);
}

bool GuiStyleCache::contains(const std::string& name) {
	std::map<std::string, GuiEntryStyle*>::iterator it = _styleCache.find(name);

	return it != _styleCache.end();
}

////////////////////////////////////////////////////////////////////////////////
// Static vars
////////////////////////////////////////////////////////////////////////////////
std::map<std::string, GuiEntryStyle*> GuiStyleCache::_styleCache;
