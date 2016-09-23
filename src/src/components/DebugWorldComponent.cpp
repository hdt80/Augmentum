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
DebugWorldComponent::DebugWorldComponent(Window* window, Vector2 pos,
					Vector2 size, Vector2 windowSize)
		: GuiComponent(window, pos, size, windowSize) {

	GameWindow* gameWindow = nullptr;
	if ((gameWindow = dynamic_cast<GameWindow*>(window)) != nullptr) {
		CORE_INFO("We were passed a GameWindow");

		_window = gameWindow;
		_map = gameWindow->getMap();
	}

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

//
void DebugWorldComponent::update(int diff) {

}

//
void DebugWorldComponent::draw(sf::RenderTarget& target,
		sf::RenderStates states) const {
	
	Ship* ship = _map->getSelected();

	sf::Text text("", FontCache::getFont("pixel"), 16);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1.0f);

	text.setString(convert::format("FPS: %u", Game::Fps.getFPS()));
	text.setPosition(0.0f, 0.0f);
	target.draw(text);

	text.setString(convert::format("Pos [%g %g]", ship->getX(), ship->getY()));
	text.setPosition(0.0f, 16.0f);
	target.draw(text);

	text.setString(convert::format("Speed: %g, %g", 
				ship->getVelocity().X, ship->getVelocity().Y));
	text.setPosition(0.0f, 32.0f);
	target.draw(text);

	//text.setString(convert::format("Goal Speed: %g, %g", 
	//			ship->getVelocityGoal().X, ship->getVelocityGoal().Y));
	//text.setPosition(0.0f, 48.0f);
	//target.draw(text);
}
