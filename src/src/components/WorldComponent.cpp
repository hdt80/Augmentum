#include "components/WorldComponent.h"
#include "Logger.h"

#include "Map.h"
#include "GameWindow.h"
#include "Ship.h"
#include "FontCache.h"
#include "Game.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor
////////////////////////////////////////////////////////////////////////////////
WorldComponent::WorldComponent(Window* window, GuiStyle* style, Vector2 pos,
		Vector2 size, Vector2 windowSize)
	: GuiComponent(window, style, pos, size, windowSize) {

	GameWindow* gameWindow = nullptr;
	if ((gameWindow = dynamic_cast<GameWindow*>(window)) != nullptr) {
		_window = gameWindow;
		_map = gameWindow->getMap();

		_map->getWorld()->SetDebugDraw(&Game::b2DebugDrawer);
	}

	_drawBounds = false;
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

	// Draw the bounds of boxes
	if (_drawBounds) {
		_map->getWorld()->DrawDebugData();	
	}
}

// Called when this Compontent is clicked on
// window_x - X coord relative to the window
// window_y - Y coord relative to the window
// view_x - X coord relative to the world
// view_y - Y cooord relative to the world
void WorldComponent::onClick(int button, float window_x, float window_y,
		float view_x, float view_y) {

	Object* obj = nullptr;

	Stats s;
	s["speed"] = 0.0f;

	if (button == sf::Mouse::Left) {
		obj = new Ship(_map, view_x, view_y, s, 15, sf::Color::Red);
	} else if (button == sf::Mouse::Right) {
		obj = new Ship(_map, view_x, view_y, s, 9, sf::Color(232, 232, 232));
	} else {
		CORE_WARN("Uncaught sf::Mouse button");
	}

	_map->objects.push_back(obj);
}
