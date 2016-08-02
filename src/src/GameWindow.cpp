#include "GameWindow.h"
#include "Logger.h"
#include "Game.h"
#include "sfLine.h"
#include "Common.h"
#include "SkillTree.h"
#include "ParticleEmitter.h"
#include "Convert.h"
#include "SkillTreeWindow.h"
#include "GuiComponent.h"
#include "Ship.h"

///////////////////////////////////////////////////////////////////////////////
// Creation Methods
///////////////////////////////////////////////////////////////////////////////
GameWindow::GameWindow(Vector2 size) {
	_size = size;
	_name = "Game Window";
	_map.setSize(size.X, size.Y);
}

GameWindow::~GameWindow() {

}

///////////////////////////////////////////////////////////////////////////////
// State Methods
///////////////////////////////////////////////////////////////////////////////
void GameWindow::init() {
	Window::init();
	SkillTrees::createTrees(_size);
	ParticleEmit::window = this;
	
	if (!_font.loadFromFile("res\\Pixel.ttf")) {
		CORE_ERROR("Failed to load \'%s\\res\\Pixel.ttf\'",
			convert::getWorkingDir().c_str());
	}
}

///////////////////////////////////////////////////////////////////////////////
// Updating Methods
///////////////////////////////////////////////////////////////////////////////
void GameWindow::update(int diff) {
	Window::update(diff);

	for (unsigned int i = 0; i < emitters.size(); ++i) {
		emitters[i]->update(diff);
	}


	float xa = sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
				sf::Keyboard::isKeyPressed(sf::Keyboard::A);

	float ya = sf::Keyboard::isKeyPressed(sf::Keyboard::S) -	
				sf::Keyboard::isKeyPressed(sf::Keyboard::W);

	_map.getSelected()->setVelocity(xa, ya);

	_map.update(diff);
}

///////////////////////////////////////////////////////////////////////////////
// SFML Method Wrapper
///////////////////////////////////////////////////////////////////////////////
void GameWindow::handleEvent(sf::Event& e) {
	Window::handleEvent(e);
}

void GameWindow::keyEvent(sf::Event& e) {
	//CORE_INFO("%d", e.key.code);
	//if (e.key.code == sf::Keyboard::Escape) {
	//	CORE_INFO("ESC");
	//} else if (e.key.code == sf::Keyboard::A) {
	//	_map.getSelected()->moveRelative(-10, 0);
	//} else if (e.key.code == sf::Keyboard::S) {
	//	_map.getSelected()->moveRelative(0, 10);
	//} else if (e.key.code == sf::Keyboard::D) {
	//	_map.getSelected()->moveRelative(10, 0);
	//} else if (e.key.code == sf::Keyboard::W) {
	//	_map.getSelected()->moveRelative(0, -10);
	//}
}

void GameWindow::mouseEvent(sf::Event& e) {
	int x = e.mouseButton.x;
	int y = e.mouseButton.y;
	if (e.mouseButton.button == sf::Mouse::Left) {
		CORE_INFO("x: %d, y: %d", x, y);
	} else if (e.mouseButton.button == sf::Mouse::Middle) {

	}
}

void GameWindow::render(sf::RenderWindow& window) {
	window.clear(sf::Color::Black);
	renderMap(window);

	for (unsigned int i = 0; i < _map.objects.size(); ++i) {
		window.draw(*_map.objects[i]);
	}
	for (unsigned int i = 0; i < emitters.size(); ++i) {
		window.draw(*emitters[i]);
	}
	Window::render(window);
}

void GameWindow::renderMap(sf::RenderWindow& window) {
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
}

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
