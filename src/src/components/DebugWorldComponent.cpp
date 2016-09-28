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
DebugWorldComponent::DebugWorldComponent(Window* window, GuiStyle* style,
			Vector2 pos, Vector2 size, Vector2 windowSize)
		: GuiComponent(window, style, pos, size, windowSize) {

	GameWindow* gameWindow = nullptr;
	if ((gameWindow = dynamic_cast<GameWindow*>(window)) != nullptr) {
		CORE_INFO("We were passed a GameWindow");

		_window = gameWindow;
		_map = gameWindow->getMap();
	}

	// Message doesn't matter now cause it's set during update
	_fps = new GuiEntry(style, "");
	_pos = new GuiEntry(style, "");
	_speed = new GuiEntry(style, "");

	addEntry(_fps, 0, 0);
	addEntry(_pos, 0, 24);
	addEntry(_speed, 0, 48);
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void DebugWorldComponent::update(int diff) {
	Ship* ship = _map->getSelected();
	_fps->setMessage(convert::format("FPS: %u", Game::Fps.getFPS()));
	_pos->setMessage(convert::format("Pos [%g %g]", ship->getX(), ship->getY()));
	_speed->setMessage(convert::format("Speed: %g, %g",
				ship->getVelocity().X, ship->getVelocity().Y));
}


//void DebugWorldComponent::draw(sf::RenderTarget& target,
//		sf::RenderStates states) const {
//	
//	Ship* ship = _map->getSelected();
//
//	sf::Text text("", FontCache::getFont("pixel"), 16);
//	text.setFillColor(sf::Color::White);
//	text.setOutlineColor(sf::Color::Black);
//	text.setOutlineThickness(1.0f);
//
//	text.setString(convert::format("FPS: %u", Game::Fps.getFPS()));
//	text.setPosition(0.0f, 0.0f);
//	target.draw(text);
//
//	text.setString(convert::format("Pos [%g %g]", ship->getX(), ship->getY()));
//	text.setPosition(0.0f, 16.0f);
//	target.draw(text);
//
//	text.setString(convert::format("Speed: %g, %g", 
//				ship->getVelocity().X, ship->getVelocity().Y));
//	text.setPosition(0.0f, 32.0f);
//	target.draw(text);
//}
