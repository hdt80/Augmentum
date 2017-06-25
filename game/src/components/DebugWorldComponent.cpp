#include "game/components/DebugWorldComponent.h"

#include "game/GameWindow.h"
#include "game/Ship.h"
#include "game/Game.h"
#include "game/FPS.h"
#include "game/util/StringUtil.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor
////////////////////////////////////////////////////////////////////////////////
DebugWorldComponent::DebugWorldComponent(Window* window,
			const GuiEntryStyle* style, const GuiComponentStyle* compStyle,
			Vector2 pos, Vector2 size)
		: GuiComponent(window, style, compStyle, pos, size) {

	_map = &Game::getMap();

	// Message doesn't matter now cause it's set during update
	_fps = new GuiEntry(this, "");
	_pos = new GuiEntry(this, "");
	_speed = new GuiEntry(this, "");
	_mousePos = new GuiEntry(this, "");

	addEntry(_fps, 0, 0);
	addEntry(_pos, 0, 24);
	addEntry(_speed, 0, 48);
	addEntry(_mousePos, 0, 72);
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void DebugWorldComponent::update(int diff) {
	GuiComponent::update(diff);
	Ship* ship = _map->getSelected();
	_fps->setMessage(StringUtil::format("FPS: %u", Game::Fps.getFPS()));
	_pos->setMessage(StringUtil::format("Pos [%g %g]",
		ship->getX(), ship->getY()));
	_speed->setMessage(StringUtil::format("Speed [%g %g]",
		ship->getVelocity().X, ship->getVelocity().Y));

	sf::Vector2i mousePos = sf::Mouse::getPosition(Game::getRenderWindow());
	_mousePos->setMessage(StringUtil::format("Mouse [%d %d]",
		mousePos.x, mousePos.y));
}
