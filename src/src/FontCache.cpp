#include "FontCache.h"
#include "Logger.h"

void FontCache::loadFont(const std::string& name, const std::string& path) {
	sf::Font font;
	if (!font.loadFromFile(path)) {
		CORE_WARN("Failed to load \'%s\' from \'%s\'",
			name.c_str(), path.c_str());
		return;
	}

	_fontCache[name] = font;
}

sf::Font& FontCache::getFont(const std::string& name) {
	if (!isLoaded(name)) {
		CORE_WARN("\'%s\' not found, returning default font", name.c_str());
		return getDefaultFont();
	}
	return _fontCache.at(name);
}

bool FontCache::isLoaded(const std::string& name) {
	std::map<std::string, sf::Font>::iterator it = _fontCache.find(name);

	return it != _fontCache.end();
}

void FontCache::setDefaultFont(const std::string& path) {
	sf::Font font;
	if (!font.loadFromFile(path)) {
		CORE_WARN("Failed to load \'%s\'", path.c_str());
		return;
	}

	_defaultFont = font;
}

////////////////////////////////////////////////////////////////////////////////
// Static vars
////////////////////////////////////////////////////////////////////////////////
std::map<std::string, sf::Font> FontCache::_fontCache;
sf::Font FontCache::_defaultFont;
