#include "components/WorldComponent.h"
#include "Logger.h"

#include "Map.h"
#include "GameWindow.h"
#include "Ship.h"
#include "Game.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor
////////////////////////////////////////////////////////////////////////////////
WorldComponent::WorldComponent(Window* window, const GuiEntryStyle* style,
		const GuiComponentStyle* compStyle, Vector2 pos, Vector2 size)
	: GuiComponent(window, style, compStyle, pos, size) {

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
	GuiComponent::update(diff);
	_view.setCenter(_map->getSelected()->getX(), _map->getSelected()->getY());
}

// Method inherited from sf::Drawable
void WorldComponent::draw(sf::RenderTarget& target,
		sf::RenderStates states) const {

	target.draw(GameWindow::Emitter);

	for (unsigned int i = 0; i < _map->objects.size(); ++i) {
		target.draw(*(_map->objects[i]), states);
	}

	// Draw the bounds of boxes
	if (_drawBounds) {
		_map->getWorld()->DrawDebugData();	
	}

	GuiComponent::draw(target, states);
}

// Called when this Compontent is clicked on
// window_x - X coord relative to the window
// window_y - Y coord relative to the window
// view_x - X coord relative to the world
// view_y - Y cooord relative to the world
void WorldComponent::onClick(int button, float window_x, float window_y,
		float view_x, float view_y) {

	GuiComponent::onClick(button, window_x, window_y, view_x, view_y);
}
