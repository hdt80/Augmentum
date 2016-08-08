#include "components/WorldComponent.h"
#include "Logger.h"

#include "Map.h"
#include "GameWindow.h"
#include "Ship.h"
#include "FontCache.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor
////////////////////////////////////////////////////////////////////////////////
WorldComponent::WorldComponent(Window* window, Vector2 pos,
					Vector2 size, Vector2 windowSize)
		: GuiComponent(window, pos, size, windowSize) {

	_drawBounds = true;

	GameWindow* gameWindow = nullptr;
	if ((gameWindow = dynamic_cast<GameWindow*>(window)) != nullptr) {
		_window = gameWindow;
		_map = gameWindow->getMap();
	}
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

// 
void WorldComponent::update(int diff) {
	_view.setCenter(_map->getSelected()->getX(), _map->getSelected()->getY());
}

//
void WorldComponent::draw(sf::RenderTarget& target,
		sf::RenderStates states) const {

	sf::RectangleShape boundBox;

	for (unsigned int i = 0; i < _map->objects.size(); ++i) {
		if (_drawBounds) {
			sf::FloatRect rect = _map->objects[i]->getCollisionBox();
			boundBox.setPosition(rect.left, rect.top);
			boundBox.setSize(sf::Vector2f(rect.width, rect.height));
			target.draw(boundBox);
		}

		target.draw(*(_map->objects[i]), states);
	}
}

//
void WorldComponent::onClick(float window_x, float window_y,
							 float view_x, float view_y) {

	_map->objects.push_back(new Ship(_map, view_x, view_y, 15, Stats()));
}
