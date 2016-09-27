#ifndef _FONT_CACHE_H
#define _FONT_CACHE_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class FontCache {
public:

	// Load a font and store it into the cache
	// name - Name to store the font as
	// path - Path to the font to load
	static void loadFont(const std::string& name, const std::string& path);

	// Get a loaded font
	// name - Name the the font was stored under
	static sf::Font& getFont(const std::string& name);

	// Check if a font under a name is cached
	// name - Name of the font to check
	static bool isLoaded(const std::string& name);

	static void setDefaultFont(const std::string& path);
	static sf::Font& getDefaultFont() { return _defaultFont; }

private:
	static std::map<std::string, sf::Font> _fontCache;
	static sf::Font _defaultFont;
};

#endif
