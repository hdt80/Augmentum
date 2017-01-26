#include "components/UnitStatsComponent.h"

#include "Game.h"
#include "GameWindow.h"
#include "Entity.h"

#include "util/StringUtil.h"
#include "util/ObjectUtil.h"

////////////////////////////////////////////////////////////////////////////////
// UnitStatsComponent ctor and dtor
////////////////////////////////////////////////////////////////////////////////

UnitStatsComponent::UnitStatsComponent(Window* window, 
		const GuiEntryStyle* style,	const GuiComponentStyle* compStyle,
		Vector2 pos, Vector2 size)
	: GuiComponent(window, style, compStyle, pos, size) {

	_hovered = nullptr;
	_map = &Game::getMap();

	_unitName = new GuiEntry(this, "");
	_unitPos = new GuiEntry(this, "");
	_unitVelocity = new GuiEntry(this, "");
	_unitLevel = new GuiEntry(this, "");
	_unitSpeed = new GuiEntry(this, "");
	_unitRange = new GuiEntry(this, "");
	_unitDamage = new GuiEntry(this, "");
	_unitFireRate = new GuiEntry(this, "");
	_unitProjSpeed = new GuiEntry(this, "");
	_unitAccel = new GuiEntry(this, "");
	_unitHp = new GuiEntry(this, "");
	_unitMaxHp = new GuiEntry(this, "");

	addEntry(_unitPos, 0, 0);
	addEntry(_unitVelocity, 0, 20);
	addEntry(_unitHp, 0, 40);
	addEntry(_unitMaxHp, 0, 60);
	addEntry(_unitLevel, 0, 80);
	addEntry(_unitSpeed, 0, 100);
	addEntry(_unitRange, 0, 120);
	addEntry(_unitDamage, 0, 140);
	addEntry(_unitFireRate, 0, 160);
	addEntry(_unitProjSpeed, 0, 180);
	addEntry(_unitAccel, 0, 200);
	addEntry(_unitName, 0, 220);
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

	_hovered = dynamic_cast<Entity*>(_map->objectAt(nullptr,
		worldPos.x, worldPos.y));

	if (_hovered) {
		_unitPos->setMessage(StringUtil::format("Pos [%g, %g]",
			_hovered->getX(), _hovered->getY()));
		_unitVelocity->setMessage(StringUtil::format("Vel [%g, %g]",
			_hovered->getVelocity().X, _hovered->getVelocity().Y));
		_unitHp->setMessage(StringUtil::format("Health: %g",
			_hovered->getHealth()));
		_unitMaxHp->setMessage(StringUtil::format("Max health: %g",
			_hovered->getMaxHealth()));

		Unit* u = nullptr;
		if ((u = ObjectUtil::toType<Unit>(_hovered))) {
			_unitLevel->setMessage(StringUtil::format("Lvl: %d, Exp: %g",
				u->getLevel(), u->getExp()));
			_unitSpeed->setMessage(StringUtil::format("Speed: %g", 
				u->getSpeed()));
			_unitRange->setMessage(StringUtil::format("Range: %g",
				u->getRange()));
			_unitDamage->setMessage(StringUtil::format("Damage: %g",
				u->getDamage()));
			_unitFireRate->setMessage(StringUtil::format("FireRate: %g",
				u->getFireRate()));
			_unitAccel->setMessage(StringUtil::format("Accel: %g",
				u->getAccel()));
			_unitProjSpeed->setMessage(StringUtil::format("ProjSpeed: %g",
				u->getProjSpeed()));

			Enemy* e = nullptr;
			if ((e = ObjectUtil::toType<Enemy>(_hovered))) {
				_unitName->setMessage(StringUtil::format("Type: %s",
					e->getEnemyType().getName().c_str()));
			}
		}
	} else {
		_unitPos->setMessage("");
		_unitVelocity->setMessage("");
		_unitLevel->setMessage("");
		_unitHp->setMessage("");
		_unitMaxHp->setMessage("");
		_unitSpeed->setMessage("");
		_unitRange->setMessage("");
		_unitDamage->setMessage("");
		_unitFireRate->setMessage("");
		_unitAccel->setMessage("");
		_unitProjSpeed->setMessage("");
		_unitName->setMessage("");
	}
}

void UnitStatsComponent::draw(sf::RenderTarget& target,
		sf::RenderStates states) const {
	
	target.draw(*_unitPos);
	target.draw(*_unitVelocity);
	target.draw(*_unitLevel);
	target.draw(*_unitSpeed);
	target.draw(*_unitRange);
	target.draw(*_unitDamage);
	target.draw(*_unitFireRate);
	target.draw(*_unitAccel);
	target.draw(*_unitProjSpeed);
	target.draw(*_unitName);
	target.draw(*_unitHp);
	target.draw(*_unitMaxHp);
}
