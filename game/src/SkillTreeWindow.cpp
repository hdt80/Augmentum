#include "game/SkillTreeWindow.h"

#include "game/SkillTree.h"
#include "game/Game.h"
#include "game/Unit.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

SkillTreeWindow::SkillTreeWindow(SkillTree* tree, Vector2 size)
	: Window("Skill Tree", size),
		_backgroundDrawn(false), _tree(tree) {

	if (_tree == nullptr) {
		AG_WARN("Null tree recieved");
	}

	_background.setPosition(0.0f, 0.0f);
	_background.setFillColor(sf::Color(64, 64, 64, 48));
	_background.setOutlineColor(sf::Color::Black);
	_background.setOutlineThickness(-1.0f);
	_background.setSize(sf::Vector2f(_size.X, _size.Y));
}

SkillTreeWindow::~SkillTreeWindow() {
	
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

void SkillTreeWindow::pause() {
	_backgroundDrawn = false;
}

void SkillTreeWindow::update(int diff) {
	_cursor.update(diff);
}

void SkillTreeWindow::keyEvent(sf::Event& e) {
    if (e.key.code == sf::Keyboard::T) {
        Game::WindowManager.pop();
    } else if (e.key.code == sf::Keyboard::D) {
        _tree->print(_tree->getHead(), true);
    }
}

void SkillTreeWindow::mouseEvent(sf::Event& e) {
	// Node clicked on
    SkillNode* node = _tree->getNode(e.mouseButton.x, e.mouseButton.y);
    if (node) {
		node->print();
        AG_INFO("Clicked on \'%s\'", node->name().c_str());
        if (node->unlocked()) {
            node->incPoints();
			if (node->points > 0) {
				node->attached = _tree->getAttached();
				_tree->getAttached()->addPerk(node->perk);
			}
        }
    }
}

void SkillTreeWindow::render(sf::RenderWindow& window) {
	window.clear(sf::Color(180, 180, 180));
	Window::render(window);
	if (!_backgroundDrawn) {
		window.draw(_background);
		_backgroundDrawn = true;
	}
    if (_tree) {
        window.draw(*_tree);
    } else {
        AG_WARN("Tried to draw %x! An incomplete tree", _tree);
    }

	window.draw(_cursor);
}
