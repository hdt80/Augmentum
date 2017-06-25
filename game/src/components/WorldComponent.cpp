#include "game/components/WorldComponent.h"

#include "game/Map.h"
#include "game/GameWindow.h"
#include "game/Ship.h"
#include "game/Game.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor
////////////////////////////////////////////////////////////////////////////////

WorldComponent::WorldComponent(Window* window, const GuiEntryStyle* style,
		const GuiComponentStyle* compStyle, Vector2 pos, Vector2 size)
	: GuiComponent(window, style, compStyle, pos, size) {

	_map = &Game::getMap();
	_map->getWorld()->SetDebugDraw(&Game::b2DebugDrawer);

	_drawBounds = false;
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void WorldComponent::update(int diff) {
	GuiComponent::update(diff);
	_view.setCenter(_map->getSelected()->getX(), _map->getSelected()->getY());
}

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

void WorldComponent::onClick(int button, float window_x, float window_y,
		float view_x, float view_y) {

	GuiComponent::onClick(button, window_x, window_y, view_x, view_y);
}
