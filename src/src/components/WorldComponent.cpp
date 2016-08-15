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

	GameWindow* gameWindow = nullptr;
	if ((gameWindow = dynamic_cast<GameWindow*>(window)) != nullptr) {
		_window = gameWindow;
		_map = gameWindow->getMap();
	}
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

// Update this Component
// diff - Milliseconds since the last update
void WorldComponent::update(int diff) {
	_view.setCenter(_map->getSelected()->getX(), _map->getSelected()->getY());
}

// Method inherited from sf::Drawable
void WorldComponent::draw(sf::RenderTarget& target,
		sf::RenderStates states) const {

	for (unsigned int i = 0; i < _map->objects.size(); ++i) {
		target.draw(*(_map->objects[i]), states);
	}
}

// Called when this Compontent is clicked on
// window_x - X coord relative to the window
// window_y - Y coord relative to the window
// view_x - X coord relative to the world
// view_y - Y cooord relative to the world
void WorldComponent::onClick(float window_x, float window_y,
		float view_x, float view_y) {

	Ship* ship = new Ship(_map, view_x, view_y, Stats(), 15, sf::Color::Red);

	_map->objects.push_back(ship);
}
