#include "GameWindow.h"

#include "Logger.h"
#include "Game.h"
#include "LuaConfig.h"
#include "Ship.h"
#include "environment/Asteroid.h"
#include "Database.h"

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

GameWindow::GameWindow(Vector2 size) {
	_size = size;
	_name = "Game Window";
	_drawFps = false;

	sf::Font font;
	if (!font.loadFromFile("res/Pixel.ttf")) {
		CORE_WARN("Couldn't load \'%s\'", "Pixel.ttf");
	}

	Databases::FontDatabase.setDefault(font);
	Databases::FontDatabase.store("pixel", font);

	_fpsText.setPosition(12, _size.Y - 40);
	_fpsText.setFont(Databases::FontDatabase.getDefault());
	_fpsText.setOutlineThickness(1.0f);
	_fpsText.setOutlineColor(sf::Color::Black);
	_fpsText.setFillColor(sf::Color::White);

	_particleCountText.setPosition(12, _size.Y - 80);
	_particleCountText.setFont(Databases::FontDatabase.getDefault());
	_particleCountText.setOutlineThickness(1.0f);
	_particleCountText.setOutlineColor(sf::Color::Black);
	_particleCountText.setFillColor(sf::Color::White);

	GuiEntryStyle::loadFromFile("./lua/gui_styles/entry_styles.lua");
	GuiProgressBarStyle::loadFromFile("./lua/gui_styles/progbar_styles.lua");
	GuiComponentStyle::loadFromFile("./lua/gui_styles/comp_styles.lua");

	GuiToolbarComponent* hud = new GuiToolbarComponent(this,
		&Databases::GuiEntryStyleDatabase.get("hud"),
		&Databases::GuiComponentStyleDatabase.get("trans"),
		Vector2(0, 0), Vector2(_size.X, 60), true);

	GuiToolbarComponent* toolbar = new GuiToolbarComponent(this,
		&Databases::GuiEntryStyleDatabase.get("toolbar"),
		&Databases::GuiComponentStyleDatabase.get("style"),
		Vector2(8, 8), Vector2(_size.X - 48, 96), true);

	WorldComponent* worldComp = new WorldComponent(this,
		&Databases::GuiEntryStyleDatabase.get("world"),
		&Databases::GuiComponentStyleDatabase.get("trans"),
		Vector2(0.0, 0.0), Vector2(_size.X, _size.Y));
	
	DebugWorldComponent* dComp = new DebugWorldComponent(this,
		&Databases::GuiEntryStyleDatabase.get("debug"),
		&Databases::GuiComponentStyleDatabase.get("style"),
		Vector2(_size.X - 180, 0), Vector2(180, _size.Y));

	UnitStatsComponent* usComp = new UnitStatsComponent(this,
		&Databases::GuiEntryStyleDatabase.get("debug"),
		&Databases::GuiComponentStyleDatabase.get("trans"),
		Vector2(8, 64), Vector2(240, _size.Y - 24));

	hud->addEntry(new GuiProgressBar(hud, "HP",
		&Databases::GuiProgressBarStyleDatabase.get("hp_bar"),
		&Game::getMap().getSelected()->getHealth(), 0,
		&Game::getMap().getSelected()->getMaxHealth()));

	hud->addEntry(new GuiExpProgressBar(hud, "EXP",
		&Databases::GuiProgressBarStyleDatabase.get("exp_bar"),
		Game::getMap().getSelected()), 0, 48);

	toolbar->addEntry(new GuiMenuButton(toolbar, "Debug", dComp));

	//addComponent(toolbar);
	//addComponent(dComp);
	addComponent(hud);
	addComponent(worldComp);
	addComponent(usComp);

	def.lifetime = 3.0f;
	def.coneOfDispersion = 15.0f;
	def.speedVariation = 0.0f;
	def.initColor = sf::Color(255, 0, 0);
	def.endColor = def.initColor;
	def.fade = true;
	def.speed = 30.0f;
	def.slowDown = false;
	Databases::ParticleDefDatabase.store("test_parts", def);

	ParticleDef levelPDef;
	levelPDef.lifetime = 3.0f;
	levelPDef.coneOfDispersion = 360.0f;
	levelPDef.speedVariation = 20.0f;
	levelPDef.initColor = sf::Color(80, 80, 255);
	levelPDef.endColor = levelPDef.initColor;
	levelPDef.fade = true;
	levelPDef.speed = 50.0f;
	levelPDef.slowDown = false;
	Databases::ParticleDefDatabase.store("level_up", levelPDef);

	ParticleDef asteroid_death;
	asteroid_death = levelPDef;
	asteroid_death.initColor = sf::Color(80, 80, 80);
	asteroid_death.endColor = asteroid_death.initColor;
	Databases::ParticleDefDatabase.store("asteroid_death", asteroid_death);

	ParticleDef hitDef;
	hitDef.lifetime = 2.0f;
	hitDef.coneOfDispersion = 45.0f;
	hitDef.speedVariation = 20.0f;
	hitDef.initColor = sf::Color(255, 0, 0);
	hitDef.endColor = sf::Color(220, 0, 0);
	hitDef.fade = true;
	hitDef.speed = 30.0f;
	hitDef.slowDown = false;
	Databases::ParticleDefDatabase.store("hit", hitDef);
}

GameWindow::~GameWindow() {

}

///////////////////////////////////////////////////////////////////////////////
// State Methods
///////////////////////////////////////////////////////////////////////////////

void GameWindow::init() {
	Window::init();
	SkillTrees::createTrees(_size);
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
	}
}

void GameWindow::mouseEvent(sf::Event& e) {
	Vector2 worldPos = 
		SFMLUtil::getRelativeMouseClick(e.mouseButton.x, e.mouseButton.y, this);

	if (e.mouseButton.button == sf::Mouse::Left) {
		Game::getMap().getSelected()->shoot(worldPos.X, worldPos.Y);
	} else if (e.mouseButton.button == sf::Mouse::Right) {
		Game::getMap().spawnEnemy(worldPos.X, worldPos.Y, 2, -1);
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
