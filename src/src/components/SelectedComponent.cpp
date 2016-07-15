#include "components/SelectedComponent.h"
#include "GameWindow.h"
#include "Tower.h"

SelectedComponent::SelectedComponent() {
	_selected = nullptr;
}

SelectedComponent::SelectedComponent(GameWindow* window) :
	GuiComponent(Vector2(window->getWidth() - 240, 0),
			Vector2(240, window->getHeight()),
			window->getSize()) {

	this->_sel = window->getSel();
}

SelectedComponent::~SelectedComponent() {

}


////////////////////////////////////////////////////////////////////////////////
// Update methods
////////////////////////////////////////////////////////////////////////////////
void SelectedComponent::update(int diff) {
}

void SelectedComponent::draw(sf::RenderTarget& target,
		sf::RenderStates stats) const {

	sf::RectangleShape box;
	box.setPosition(0.0f, 0.0f);
	box.setFillColor(sf::Color(127, 127, 127, 127));
	box.setOutlineColor(sf::Color::White);
	box.setOutlineThickness(30.0f);
	box.setSize(sf::Vector2f(_size.X, _size.Y));

	sf::Text text;

	target.draw(box);
}
