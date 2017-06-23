#include "GameWindow.h"

#include "Logger.h"
#include "Game.h"
#include "LuaConfig.h"
#include "Ship.h"
#include "environment/Asteroid.h"
#include "Database.h"
#include "Databases.h"

#include "SkillTree.h"
#include "SkillTreeWindow.h"

#include "components/WorldComponent.h"
#include "components/DebugWorldComponent.h"
#include "components/UnitStatsComponent.h"

#include "gui/GuiComponent.h"
#include "gui/GuiToolbarComponent.h"
#include "gui/GuiButton.h"
#include "gui/GuiMenuButton.h"
#include "gui/GuiProgressBar.h"
#include "gui/GuiExpProgressBar.h"

#include "gui_style/GuiEntryStyle.h"
#include "gui_style/GuiComponentStyle.h"
#include "gui_style/GuiProgressBarStyle.h"

#include "ExperienceHelper.h"
#include "util/StringUtil.h"
#include "util/SFMLUtil.h"
#include "util/Random.h"

////////////////////////////////////////////////////////////////////////////////
// Static vars
////////////////////////////////////////////////////////////////////////////////

ParticleEmitter GameWindow::Emitter;

////////////////////////////////////////////////////////////////////////////////
// ctor and dtor
////////////////////////////////////////////////////////////////////////////////

GameWindow::GameWindow(Vector2 size)
	: _skillWindow(Game::getMap().getSelected()->getTree(), size) {
	_size = size;
	_name = "Game Window";
	_drawFps = false;

	sf::Font font;
	if (!font.loadFromFile("res/Pixel.ttf")) {
		CORE_WARN("Couldn't load \'%s\'", "Pixel.ttf");
	}

	Databases::Fonts.setDefault(font);
	Databases::Fonts.store("pixel", font);

	_fpsText.setPosition(12, _size.Y - 40);
	_fpsText.setFont(Databases::Fonts.getDefault());
	_fpsText.setOutlineThickness(1.0f);
	_fpsText.setOutlineColor(sf::Color::Black);
	_fpsText.setFillColor(sf::Color::White);

	_particleCountText.setPosition(12, _size.Y - 80);
	_particleCountText.setFont(Databases::Fonts.getDefault());
	_particleCountText.setOutlineThickness(1.0f);
	_particleCountText.setOutlineColor(sf::Color::Black);
	_particleCountText.setFillColor(sf::Color::White);

	Databases::GuiEntryStyles
		.loadFromFile("./lua/gui_styles/entry_styles.lua", "GuiEntryStyle");

	Databases::GuiComponentStyles
		.loadFromFile("./lua/gui_styles/comp_styles.lua", "GuiComponentStyle");

	Databases::GuiProgressBarStyles.loadFromFile(
		"./lua/gui_styles/progbar_styles.lua", "GuiProgressBarStyle");

	Databases::EnemyTypes
		.loadFromFile("./lua/enemies/enemies.lua", "EnemyType");

	Databases::ParticleDefs
		.loadFromFile("./lua/particles/parts.lua", "ParticleDef");

	GuiToolbarComponent* hud = new GuiToolbarComponent(this,
		&Databases::GuiEntryStyles.get("hud"),
		&Databases::GuiComponentStyles.get("trans"),
		Vector2(0, 0), Vector2(_size.X, 60), true);

	GuiToolbarComponent* toolbar = new GuiToolbarComponent(this,
		&Databases::GuiEntryStyles.get("toolbar"),
		&Databases::GuiComponentStyles.get("style"),
		Vector2(8, 8), Vector2(_size.X - 48, 96), true);

	WorldComponent* worldComp = new WorldComponent(this,
		&Databases::GuiEntryStyles.get("world"),
		&Databases::GuiComponentStyles.get("trans"),
		Vector2(0.0, 0.0), Vector2(_size.X, _size.Y));
	
	DebugWorldComponent* dComp = new DebugWorldComponent(this,
		&Databases::GuiEntryStyles.get("debug"),
		&Databases::GuiComponentStyles.get("style"),
		Vector2(_size.X - 180, 0), Vector2(180, _size.Y));

	UnitStatsComponent* usComp = new UnitStatsComponent(this,
		&Databases::GuiEntryStyles.get("debug"),
		&Databases::GuiComponentStyles.get("trans"),
		Vector2(8, 64), Vector2(240, _size.Y - 24));

	hud->addEntry(new GuiProgressBar(hud, "HP",
		&Databases::GuiProgressBarStyles.get("hp_bar"),
		&Game::getMap().getSelected()->getHealth(), 0,
		&Game::getMap().getSelected()->getMaxHealth()));

	hud->addEntry(new GuiExpProgressBar(hud, "EXP",
		&Databases::GuiProgressBarStyles.get("exp_bar"),
		Game::getMap().getSelected()), 0, 48);

	toolbar->addEntry(new GuiMenuButton(toolbar, "Debug", dComp));

	//addComponent(toolbar);
	//addComponent(dComp);
	addComponent(hud);
	addComponent(worldComp);
	addComponent(usComp);
}

GameWindow::~GameWindow() {

}

///////////////////////////////////////////////////////////////////////////////
// State Methods
///////////////////////////////////////////////////////////////////////////////

void GameWindow::init() {
	Window::init();
}

void GameWindow::reset() {
	Window::reset();
	Game::getMap().reset();
}

void GameWindow::close() {
	Window::close();
	Game::getMap().reset();
}

///////////////////////////////////////////////////////////////////////////////
// Updating Methods
///////////////////////////////////////////////////////////////////////////////

void GameWindow::update(int diff) {
	if (Game::getMap().isGameOver()) {
		Game::WindowManager.pop();
	}

	Window::update(diff);
	
	float xa = (sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
				sf::Keyboard::isKeyPressed(sf::Keyboard::A));

	float ya = (sf::Keyboard::isKeyPressed(sf::Keyboard::S) -	
				sf::Keyboard::isKeyPressed(sf::Keyboard::W));

	Game::getMap().getSelected()->setVelocity(xa, ya);

	Game::getMap().update(diff);

	GameWindow::Emitter.update(diff);
	_cursor.update(diff);

	if (_drawFps) {
		_fpsText.setString(StringUtil::format("%d", Game::Fps.getFPS()));
		_particleCountText.setString(StringUtil::format(
			"%d", GameWindow::Emitter.getParticleCount()));
	}
}

///////////////////////////////////////////////////////////////////////////////
// SFML Method Wrapper
///////////////////////////////////////////////////////////////////////////////

void GameWindow::keyEvent(sf::Event& e) {
	Window::keyEvent(e);
	if (e.key.code == sf::Keyboard::N) {
		CORE_INFO("[GameWindow %x] Toggling on box2d shapeBit", this);
		// TODO: Dear god no
		WorldComponent* wc = dynamic_cast<WorldComponent*>(_components[1]);
		if (wc == nullptr) {
			CORE_WARN("wc isn't 1");
			return;
		}
		Game::b2DebugDrawer.SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);
		CORE_INFO("b2DebugDraw flags: %d", Game::b2DebugDrawer.GetFlags());
		wc->setDrawBounds(!wc->getDrawBounds());
	} else if (e.key.code == sf::Keyboard::Y) {
		Game::getMap().getSelected()->setHealth(
			Game::getMap().getSelected()->getHealth() - 1);
	} else if (e.key.code == sf::Keyboard::U) {
		Game::getMap().getSelected()->setHealth(
			Game::getMap().getSelected()->getHealth() + 1);
	} else if (e.key.code == sf::Keyboard::H) {
		Game::getMap().getSelected()->addExp(1.0f);
	} else if (e.key.code == sf::Keyboard::J) {
		Game::getMap().getSelected()->addExp(-1.0f);
	} else if (e.key.code == sf::Keyboard::F) {
		_drawFps = !_drawFps;
	} else if (e.key.code == sf::Keyboard::C) {
		// Mouse relative to the window
		sf::Vector2i pixelPos = sf::Mouse::getPosition(Game::getRenderWindow());

		Vector2 worldPos = SFMLUtil::getRelativeMouseClick(
			pixelPos.x, pixelPos.y, this);

		Game::getMap().spawnAsteroid(
			worldPos.X, worldPos.Y, Random::randFloat(30, 60));
	} else if (e.key.code == sf::Keyboard::T) {
		Game::followWindow(&_skillWindow);
	}
}

void GameWindow::mouseEvent(sf::Event& e) {
	Vector2 worldPos = 
		SFMLUtil::getRelativeMouseClick(e.mouseButton.x, e.mouseButton.y, this);

	if (e.mouseButton.button == sf::Mouse::Left) {
		Game::getMap().getSelected()->shoot(worldPos.X, worldPos.Y);
	} else if (e.mouseButton.button == sf::Mouse::Right) {
		Game::getMap().spawnEnemy(worldPos.X, worldPos.Y, "lua_loaded_et1", -1);
	}
}

void GameWindow::render(sf::RenderWindow& window) {
	window.clear(sf::Color(180, 180, 180));

	Window::render(window);
	window.draw(_cursor); // Draw cursor on top

	if (_drawFps) {
		window.draw(_fpsText);
		window.draw(_particleCountText);
	}
}
