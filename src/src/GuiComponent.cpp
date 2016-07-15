#include "GuiComponent.h"
#include "Logger.h"


GuiComponent::GuiComponent() {}

GuiComponent::GuiComponent(Vector2 pos, Vector2 size, Vector2 windowSize) {
	// Components start at (0, 0) and not the position because a view represents
	// a view to a part of a drawing target, and we're drawn to (0, 0)
	_view.reset(sf::FloatRect(0, 0, size.X, size.Y));

	_pos = pos;
	_size = size;

	resize(windowSize);

	_visible = true;
	_updating = true;
}

GuiComponent::~GuiComponent() {

}


///////////////////////////////////////////////////////////////////////////////
// Update methods
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Event methods
///////////////////////////////////////////////////////////////////////////////
void GuiComponent::resize(Vector2 newSize) {
	// Views use a ratio of 0.0 to 1.0 to determine how much of the screen
	// to use. Since we provide the position and size in pixels, we convert them
	float origin_x = _pos.X / newSize.X;
	float origin_y = _pos.Y / newSize.Y;
	float r_width = _size.X / newSize.X;
	float r_height = _size.Y / newSize.Y;
	_view.setViewport(sf::FloatRect(origin_x, origin_y, r_width, r_height));
}
void GuiComponent::update(int diff) {

}

void GuiComponent::draw(sf::RenderTarget& target,
		sf::RenderStates states) const {

}
