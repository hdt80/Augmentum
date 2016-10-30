#include "components/UnitStatsComponent.h"

#include "Game.h"
#include "GameWindow.h"
#include "Convert.h"

////////////////////////////////////////////////////////////////////////////////
// UnitStatsComponent ctor and dtor
////////////////////////////////////////////////////////////////////////////////

UnitStatsComponent::UnitStatsComponent(Window* window, 
		const GuiEntryStyle* style,	const GuiComponentStyle* compStyle,
		Vector2 pos, Vector2 size)
	: GuiComponent(window, style, compStyle, pos, size) {

	_hovered = nullptr;

	GameWindow* gameWindow = nullptr;
	if ((gameWindow = dynamic_cast<GameWindow*>(window)) != nullptr) {
		_window = gameWindow;
		_map = gameWindow->getMap();
	}

	_unitPos = new GuiEntry(style, pos, "");
	_unitVelocity = new GuiEntry(style, pos, "");
	_unitSpeed = new GuiEntry(style, pos, "");
	_unitRange = new GuiEntry(style, pos, "");
	_unitDamage = new GuiEntry(style, pos, "");
	_unitFireRate = new GuiEntry(style, pos, "");
	_unitProjSpeed = new GuiEntry(style, pos, "");
	_unitAccel = new GuiEntry(style, pos, "");

	addEntry(_unitPos, 0, 0);
	addEntry(_unitVelocity, 0, 20);
	addEntry(_unitSpeed, 0, 40);
	addEntry(_unitRange, 0, 60);
	addEntry(_unitDamage, 0, 80);
	addEntry(_unitFireRate, 0, 100);
	addEntry(_unitProjSpeed, 0, 120);
	addEntry(_unitAccel, 0, 140);
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void UnitStatsComponent::update(int diff) {
	// Mouse relative to the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(Game::getRenderWindow());
	GuiComponent* clicked = 
		_window->getComponentAt(pixelPos.x, pixelPos.y);

	if (!clicked) {
		return;
	}

	// Mouse relative to the clicked GuiComponent
	sf::Vector2f worldPos = Game::getRenderWindow()
		.mapPixelToCoords(pixelPos, clicked->getView());

	_hovered = dynamic_cast<Unit*>(_map->objectAt(nullptr,
				worldPos.x, worldPos.y));

	if (_hovered) {
		_unitPos->setMessage(convert::format("Pos [%g, %g]",
			_hovered->getX(), _hovered->getY()));
		_unitVelocity->setMessage(convert::format("Vel [%g, %g]",
			_hovered->getVelocity().X, _hovered->getVelocity().Y));
		_unitSpeed->setMessage(convert::format("Speed: %g", 
			_hovered->getSpeed()));
		_unitRange->setMessage(convert::format("Range: %g",
			_hovered->getRange()));
		_unitDamage->setMessage(convert::format("Damage: %g",
			_hovered->getDamage()));
		_unitFireRate->setMessage(convert::format("FireRate: %g",
			_hovered->getFireRate()));
		_unitAccel->setMessage(convert::format("Accel: %g",
			_hovered->getAccel()));
		_unitProjSpeed->setMessage(convert::format("ProjSpeed: %g",
			_hovered->getProjSpeed()));
	} else {
		_unitPos->setMessage("");
		_unitVelocity->setMessage("");
		_unitSpeed->setMessage("");
		_unitRange->setMessage("");
		_unitDamage->setMessage("");
		_unitFireRate->setMessage("");
		_unitAccel->setMessage("");
		_unitProjSpeed->setMessage("");
	}
}

void UnitStatsComponent::draw(sf::RenderTarget& target,
		sf::RenderStates states) const {
	
	target.draw(*_unitPos);
	target.draw(*_unitVelocity);
	target.draw(*_unitSpeed);
	target.draw(*_unitRange);
	target.draw(*_unitDamage);
	target.draw(*_unitFireRate);
	target.draw(*_unitAccel);
	target.draw(*_unitProjSpeed);

}
