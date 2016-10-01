#include "components/DebugWorldComponent.h"
#include "GameWindow.h"
#include "FontCache.h"
#include "Ship.h"
#include "Convert.h"
#include "Game.h"
#include "FPS.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor
////////////////////////////////////////////////////////////////////////////////
DebugWorldComponent::DebugWorldComponent(Window* window,
			const GuiEntryStyle* style, const GuiComponentStyle* compStyle,
			Vector2 pos, Vector2 size)
		: GuiComponent(window, style, compStyle, pos, size) {

	GameWindow* gameWindow = nullptr;
	if ((gameWindow = dynamic_cast<GameWindow*>(window)) != nullptr) {
		CORE_INFO("We were passed a GameWindow");

		_window = gameWindow;
		_map = gameWindow->getMap();
	}

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
	_fps->setMessage(convert::format("FPS: %u", Game::Fps.getFPS()));
	_pos->setMessage(convert::format("Pos [%g %g]", ship->getX(), ship->getY()));
	_speed->setMessage(convert::format("Speed [%g %g]",
				ship->getVelocity().X, ship->getVelocity().Y));

	sf::Vector2i mousePos = sf::Mouse::getPosition(Game::getRenderWindow());
	_mousePos->setMessage(convert::format("Mouse [%d %d]",
				mousePos.x, mousePos.y));
}
