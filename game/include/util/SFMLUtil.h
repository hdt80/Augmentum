#pragma once

#include "game/Vector2.h"

#include <SFML/Graphics.hpp>

#include <vector>

class Window;

namespace SFMLUtil {

	// Get the position of the mouse relative to a Window
	// mousex - X position of the mouse, relative to the top left of the game
	// mousey - Y position of the mouse, relative to the top left of the game
	// window - Window to get the click relative to
	Vector2 getRelativeMouseClick(float mousex, float mousey, Window* window);

	// Wrap text to a certain length
	// text - Text to wrap to the length.
	// length - Length to wrap to in pixels. The position of the text is
	//		not taken into account and must be taken into account when
	//		the length is passed when calling
	// returns: A vector containing the strings used the wrap the text to a 
	//		certain length. These strings will only work with the font and size
	//		used by text and not any other sf::Text, not even if the string
	//		in the text is the same.
	std::vector<sf::String> wrapText(const sf::Text& text, int length);
}
