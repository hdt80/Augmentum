#include "game/util/SFMLUtil.h"

#include "game/Game.h"
#include "game/Window.h"
#include "game/gui/GuiComponent.h"

#include <SFML/Graphics.hpp>

namespace SFMLUtil {

	Vector2 getRelativeMouseClick(float mousex, float mousey, Window* window) {
		GuiComponent* clicked = 
			window->getComponentAt(mousex, mousey);

		if (clicked == nullptr) {
			AG_WARN("No GuiComponent at (%g, %g). Returning (-1, -1)",
				mousex, mousey);

			return Vector2(-1.0f, -1.0f);
		}

		// Mouse relative to the clicked GuiComponent
		sf::Vector2f worldPos = Game::getRenderWindow()
			.mapPixelToCoords(sf::Vector2i(mousex, mousey), clicked->getView());

		return Vector2(worldPos.x, worldPos.y);
	}

	std::vector<sf::String> wrapText(const sf::Text& text, int length) {
		std::vector<sf::String> toReturn;

		if (text.getLocalBounds().width <= length) {
			toReturn.push_back(sf::String(text.getString()));
			return toReturn;
		}

		sf::Text newText = text;

		while (newText.getLocalBounds().width > length) {
			// Iterate backwards to find the first char that isn't longer
			// than the length
			for (int i = newText.getString().getSize(); i >= 0; --i) {
				// If the current character's position is less than the length
				// we need to wrap to we've found the next character to make
				// the sf::String that we're pushing back to the std::vector
				if (newText.getLocalBounds().width < length) {
					toReturn.push_back(newText.getString());
					break;
				}
				if (newText.findCharacterPos(i).x <= length) {
					sf::String temp = newText.getString();
	
					// Copy only the characters up to the one before the rest
					// of the text that's being wrapped
					toReturn.push_back(temp.substring(0, i));

					// Same process with the next string
					newText.setString(temp.substring(i));
					continue;
				}
			}
		}

		return toReturn;
	}
};
