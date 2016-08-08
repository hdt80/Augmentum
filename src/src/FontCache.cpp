#include "FontCache.h"
#include "Logger.h"

//
void FontCache::loadFont(std::string name, std::string path) {
	sf::Font font;
	if (!font.loadFromFile(path)) {
		CORE_WARN("Failed to load \'%s\' from \'%s\'",
			name.c_str(), path.c_str());
	}

	_fontCache[name] = font;
}

// Get a loaded font
// name - Name of the font to load
// If the font is not loaded the default font is returned
const sf::Font& FontCache::getFont(std::string name) {
	if (!isLoaded(name)) {
		CORE_WARN("Could not load \'%s\'. Not loaded!", name.c_str());
	}
	return _fontCache.at(name);
}

// Return if a font is cached under a name
// name - Name of the font to check
bool FontCache::isLoaded(std::string name) {
	std::map<std::string, sf::Font>::iterator it = _fontCache.find(name);

	return it != _fontCache.end();
}

////////////////////////////////////////////////////////////////////////////////
// Static vars
////////////////////////////////////////////////////////////////////////////////
std::map<std::string, sf::Font> FontCache::_fontCache;
