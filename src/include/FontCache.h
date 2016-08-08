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
	static void loadFont(std::string name, std::string path);

	// Get a loaded font
	// name - Name the the font was stored under
	static const sf::Font& getFont(std::string name);

	// Check if a font under a name is cached
	// name - Name of the font to check
	static bool isLoaded(std::string name);

	static void setDefaultFont(std::string name, std::string path);
	static sf::Font getDefaultFont();

private:
	static std::map<std::string, sf::Font> _fontCache;
};

#endif
