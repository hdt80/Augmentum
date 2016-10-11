#include "GameWindow.h"
#include "Logger.h"
#include "Game.h"
#include "Common.h"
#include "SkillTree.h"
#include "Convert.h"
#include "SkillTreeWindow.h"
#include "GuiComponent.h"
#include "Ship.h"
#include "components/WorldComponent.h"
#include "components/DebugWorldComponent.h"
#include "GuiToolbarComponent.h"
#include "GuiButton.h"
#include "GuiMenuButton.h"
#include "GuiProgressBar.h"

ParticleEmitter GameWindow::Emitter;

///////////////////////////////////////////////////////////////////////////////
// Creation Methods
///////////////////////////////////////////////////////////////////////////////
GameWindow::GameWindow(Vector2 size) {
	_size = size;
	_name = "Game Window";

	sf::Font font;
	if (font.loadFromFile("res/Pixel.ttf")) {
		CORE_WARN("Couldn't load \'%s\'", "Pixel.ttf");
	}

	Databases::FontDatabase.setDefault(font);

	// Style used in the world
	GuiEntryStyle* worldStyle = new GuiEntryStyle();
	worldStyle->font = Databases::FontDatabase.getDefault();
	worldStyle->bodyColor = sf::Color(128, 128, 128);
	worldStyle->borderColor = sf::Color(180, 180, 180);
	worldStyle->textColor = sf::Color::White;
	worldStyle->highlightedColor = sf::Color(24, 24, 24);
	worldStyle->highlightedBorderColor = sf::Color(220, 220, 220);
	worldStyle->highlightedTextColor = sf::Color(80, 80, 160);
	worldStyle->dimensions = Vector2(180, 20);
	worldStyle->borderSize = 1.0f;
	worldStyle->padding = 0;
	worldStyle->textSize = -1;
	Databases::GuiEntryStyleDatabase.store("world_style", *worldStyle);

	// Style used in the debug panel
	GuiEntryStyle* debugStyle = new GuiEntryStyle(*worldStyle);
	debugStyle->bodyColor = sf::Color::Transparent;
	debugStyle->borderColor = sf::Color::Transparent;
	debugStyle->highlightedColor = sf::Color::Transparent;
	debugStyle->highlightedBorderColor = sf::Color::Transparent;
	debugStyle->highlightedTextColor = sf::Color::Transparent;
	Databases::GuiEntryStyleDatabase.store("debug_style", *debugStyle);

	// Style used in the HUD
	GuiEntryStyle* hudStyle = new GuiEntryStyle(*debugStyle);
	hudStyle->dimensions = Vector2(_size.X, 30);

	// Progress bar for a health bar
	GuiProgressBarStyle* progBar = new GuiProgressBarStyle();
	progBar->minColor = sf::Color::Red;
	progBar->maxColor = sf::Color::Green;
	Databases::GuiProgressBarStyleDatabase.store("hp_bar", *progBar);

	//
	GuiComponentStyle* compStyle = new GuiComponentStyle();
	compStyle->bodyColor = sf::Color(64, 64, 64);
	compStyle->borderColor = sf::Color(180, 180, 180);
	compStyle->borderSize = 1.0f;
	Databases::GuiComponentStyleDatabase.store("style", *compStyle);

	// Style with a transparent background
	GuiComponentStyle* transStyle = new GuiComponentStyle();
	transStyle->bodyColor = sf::Color::Transparent;
	transStyle->borderColor = sf::Color::Transparent;
	transStyle->borderSize = 0;
	Databases::GuiComponentStyleDatabase.store("trans", *transStyle);

	GuiEntryStyle* toolbarStyle = new GuiEntryStyle(*debugStyle);
	toolbarStyle->dimensions = Vector2(64, 24);

	GuiComponent* hud = new GuiComponent(this, hudStyle, transStyle,
			Vector2(0, 0), Vector2(_size.X, 48));

	GuiToolbarComponent* toolbar = new GuiToolbarComponent(this, toolbarStyle,
			Databases::GuiComponentStyleDatabase.get("style"),
			Vector2(8, 8), Vector2(_size.X - 48, 96), true);

	WorldComponent* worldComp = new WorldComponent(this, worldStyle, transStyle,
			Vector2(0.0, 0.0), Vector2(_size.X, _size.Y));
	
	DebugWorldComponent* dComp = new DebugWorldComponent(this, debugStyle,
			compStyle, Vector2(_size.X - 180, 0), Vector2(180, _size.Y));

	hud->addEntry(new GuiProgressBar(hud->getEntryStyle(), hud->getPos(),
			"HP", progBar, &_map.getSelected()->getHealth(),
			_map.getSelected()->getMaxHealth()));

	toolbar->addEntry(new GuiMenuButton(toolbar->getEntryStyle(),
			toolbar->getPos(), "Debug", dComp));

	addComponent(toolbar);
	addComponent(worldComp);
	addComponent(dComp);
	addComponent(hud);

	def.lifetime = 3.0f;
	def.coneOfDispersion = 15.0f;
	def.initColor = sf::Color(255, 0, 0);
	def.endColor = def.initColor;
	def.fade = true;
	def.speed = 30.0f;
	def.slowDown = false;
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

///////////////////////////////////////////////////////////////////////////////
// Updating Methods
///////////////////////////////////////////////////////////////////////////////
void GameWindow::update(int diff) {
	Window::update(diff);
	
	float xa = (sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
				sf::Keyboard::isKeyPressed(sf::Keyboard::A));

	float ya = (sf::Keyboard::isKeyPressed(sf::Keyboard::S) -	
				sf::Keyboard::isKeyPressed(sf::Keyboard::W));

	_map.getSelected()->setVelocity(xa, ya);

	_map.update(diff);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		sf::Vector2i pos = sf::Mouse::getPosition(Game::getRenderWindow());
		GameWindow::Emitter.emit(&def, pos.x, pos.y, 5, -10);
	}

	GameWindow::Emitter.update(diff);
	_cursor.update(diff);
}

///////////////////////////////////////////////////////////////////////////////
// SFML Method Wrapper
///////////////////////////////////////////////////////////////////////////////

//
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
	} else if (e.key.code == sf::Keyboard::M) {
		b2Body* bodies = _map.getWorld()->GetBodyList();
		for (int i = 0; i < _map.getWorld()->GetBodyCount(); ++i) {
			CORE_INFO("%d/%d :: (%g, %g)", i, _map.getWorld()->GetBodyCount(),
					bodies[i].GetPosition().x, bodies[i].GetPosition().y);
		}
	} else if (e.key.code == sf::Keyboard::Y) {
		_map.getSelected()->setHealth(_map.getSelected()->getHealth() - 1);
	} else if (e.key.code == sf::Keyboard::U) {
		_map.getSelected()->setHealth(_map.getSelected()->getHealth() + 1);
	}
}

//
void GameWindow::mouseMoveEvent(sf::Event& e) {
	Window::mouseMoveEvent(e);
}

void GameWindow::render(sf::RenderWindow& window) {
	window.clear(sf::Color(180, 180, 180));
	window.draw(GameWindow::Emitter);

	Window::render(window);
	window.draw(_cursor); // Draw cursor on top
}

//void GameWindow::renderMap(sf::RenderWindow& window) {
//	// Drawing the path enemies will take
//	Path* path = _map.getPath();
//
//	// Start the path at the first point
//	sf::Vector2f prev(path->getPoint(0)->X, path->getPoint(0)->Y);
//	sf::Vector2f curr(0, 0); // Current point we're drawing the line to
//
//	// Start at the second point, we've already gotten to first point
//	for (unsigned int i = 1; i < path->size(); ++i) {
//		curr.x = path->getPoint(i)->X;
//		curr.y = path->getPoint(i)->Y;
//
//		sfLine s(prev, curr, PATH_WIDTH);
//
//		// Create a circle at the end of the line for curved edges
//		// Radius is the thickness / 2
//		sf::CircleShape c(PATH_WIDTH / 2);
//		// Position is based on the top left point, so center it based on
//		// the radius
//		c.setPosition(sf::Vector2f(curr.x - PATH_WIDTH / 2, 
//								   curr.y - PATH_WIDTH / 2));
//		prev = curr;
//
//		window.draw(s);
//		window.draw(c);
//	}
//}

//void GameWindow::renderSelected(sf::RenderWindow& window) {
//	// Don't draw anything if nothing is selected
//	if (_selected == nullptr) {
//		return;
//	}
//
//	// Draw range of the object
//	sf::CircleShape r(_selected->getRange());
//	r.setPosition(_selected->getX() - _selected->getRange(),
//		_selected->getY() - _selected->getRange());
//
//	r.setFillColor(sf::Color(127, 255, 127, 86));
//	window.draw(r);
//
//	// Tower is shooting at something? Draw on top of range
//	if (_selected->getTarget() != nullptr) {
//		sfLine l(sf::Vector2f(_selected->getX(), _selected->getY()),
//			sf::Vector2f(_selected->getTarget()->getX(),
//			_selected->getTarget()->getY()), 1, sf::Color(255, 0, 0, 128));
//
//		window.draw(l);
//	}
//
//	// Drawing perks
//
//	// Box we'll be drawing everything from
//	sf::RectangleShape box(sf::Vector2f(PERK_BOX_WIDTH, getHeight()));
//
//	// Draw background box
//	box.setFillColor(sf::Color(112, 112, 112));
//	box.setOutlineColor(sf::Color(200, 200, 200));
//	box.setOutlineThickness(2); // Defaults to 0, or no outline
//	box.setPosition(getWidth() - PERK_BOX_WIDTH, 0);
//	window.draw(box);
//
//	// Draw each perk, with stack count and progress bar
//	for (unsigned int i = 0; i < _selected->perkCount(); ++i) {
//		// Max of 8 perks
//		box.setSize(sf::Vector2f(PERK_BOX_WIDTH, getHeight() / 8));
//		box.setFillColor(sf::Color(64, 64, 64));
//		box.setPosition(getWidth() - PERK_BOX_WIDTH, (getHeight() / 8) * i);
//
//		// Draw we'll draw the name to
//		sf::Text text(_selected->getPerk(i)->getTitle(), _font);
//		text.setPosition(box.getPosition());
//		text.setColor(sf::Color(255, 255, 255));
//		window.draw(box);
//		window.draw(text);
//
//		// Draw red background for duration bar
//		box.setFillColor(sf::Color::Red);
//		// Bar fills up half of the box, so 1/16 is half a box
//		box.setSize(sf::Vector2f(PERK_BOX_WIDTH, getHeight() / 16));
//		box.setPosition(getWidth() - PERK_BOX_WIDTH,
//			(getHeight() / 16) + ((getHeight() / 8) * i));
//		window.draw(box);
//
//		// Draw green background for duration bar
//		float percent = _selected->getPerk(i)->getDuration() /
//			_selected->getPerk(i)->getMaxDuration();
//		box.setFillColor(sf::Color::Green);
//		box.setSize(sf::Vector2f(PERK_BOX_WIDTH * percent, getHeight() / 16));
//		window.draw(box);
//	}
//}
