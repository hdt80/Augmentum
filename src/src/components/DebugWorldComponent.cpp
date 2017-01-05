#include "components/DebugWorldComponent.h"
#include "GameWindow.h"
#include "Ship.h"
#include "Game.h"
#include "FPS.h"
#include "util/StringUtil.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor
////////////////////////////////////////////////////////////////////////////////
DebugWorldComponent::DebugWorldComponent(Window* window,
			const GuiEntryStyle* style, const GuiComponentStyle* compStyle,
			Vector2 pos, Vector2 size)
		: GuiComponent(window, style, compStyle, pos, size) {

	_map = &Game::getMap();

	// Message doesn't matter now cause it's set during update
	_fps = new GuiEntry(style, getPos(), "");
	_pos = new GuiEntry(style, getPos(), "");
	_speed = new GuiEntry(style, getPos(), "");
	_mousePos = new GuiEntry(style, getPos(), "");

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
