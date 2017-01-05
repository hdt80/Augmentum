#include "util/SFMLUtil.h"

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Window.h"

#include "gui/GuiComponent.h"

namespace SFMLUtil {

	Vector2 getRelativeMouseClick(float mousex, float mousey, Window* window) {
		GuiComponent* clicked = 
			window->getComponentAt(mousex, mousey);

		if (clicked == nullptr) {
			CORE_WARN("No GuiComponent at (%g, %g). Returning (-1, -1)",
				mousex, mousey);

			return Vector2(-1.0f, -1.0f);
		}

		// Mouse relative to the clicked GuiComponent
		sf::Vector2f worldPos = Game::getRenderWindow()
			.mapPixelToCoords(sf::Vector2i(mousex, mousey), clicked->getView());

		return Vector2(worldPos.x, worldPos.y);
	}
};
