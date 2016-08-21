#include "components/WorldComponent.h"
#include "Logger.h"

#include "Map.h"
#include "GameWindow.h"
#include "Ship.h"
#include "FontCache.h"
#include "bounds/PolygonBoundBox.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor
////////////////////////////////////////////////////////////////////////////////
WorldComponent::WorldComponent(Window* window, Vector2 pos,
		Vector2 size, Vector2 windowSize)
	: GuiComponent(window, pos, size, windowSize) {

	GameWindow* gameWindow = nullptr;
	if ((gameWindow = dynamic_cast<GameWindow*>(window)) != nullptr) {
		_window = gameWindow;
		_map = gameWindow->getMap();
	}
}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

// Update this Component
// diff - Milliseconds since the last update
void WorldComponent::update(int diff) {
	_view.setCenter(_map->getSelected()->getX(), _map->getSelected()->getY());
}

// Method inherited from sf::Drawable
void WorldComponent::draw(sf::RenderTarget& target,
		sf::RenderStates states) const {

	for (unsigned int i = 0; i < _map->objects.size(); ++i) {
		target.draw(*(_map->objects[i]), states);
	}

	for (unsigned int i = 0; i < _map->objects.size(); ++i) {
		BoundBox* bb = _map->objects[i]->getBoundBox();

		// Add an extra point to the last line completing the boundbox can be
		// drawn unbroken
		sf::VertexArray aa(sf::LinesStrip, bb->getPointCount() + 1);
		for (unsigned int j = 0; j < bb->getPointCount(); ++j) {
			aa[j].color = sf::Color::Blue;
			aa[j].position = sf::Vector2f(bb->getPoint(j).X, bb->getPoint(j).Y);
		}
		// Adding the last point to the array, to complete the boundbox
		aa[bb->getPointCount()].color = sf::Color::Blue;
		aa[bb->getPointCount()].position =
			sf::Vector2f(bb->getPoint(0).X, bb->getPoint(0).Y);

		target.draw(aa);
	}
}

// Called when this Compontent is clicked on
// window_x - X coord relative to the window
// window_y - Y coord relative to the window
// view_x - X coord relative to the world
// view_y - Y cooord relative to the world
void WorldComponent::onClick(int button, float window_x, float window_y,
		float view_x, float view_y) {

	Object* obj = nullptr;

	Stats s;
	s["speed"] = 0.0f;

	if (button == sf::Mouse::Left) {
		obj = new Ship(_map, view_x, view_y, s, 15, sf::Color::Red);
	} else if (button == sf::Mouse::Right) {
		obj = new Ship(_map, view_x, view_y, s, 9, sf::Color(232, 232, 232));
		
		BoundBox* bb = new PolygonBoundBox(Vector2(view_x, view_y), 9);
		bb->addPoint(Vector2(0.0f, 0.0f));
		bb->addPoint(Vector2(20.0f, 0.0f));
		bb->addPoint(Vector2(40.0f, 20.0f));
		bb->addPoint(Vector2(40.0f, 40.0f));
		bb->addPoint(Vector2(20.0f, 60.0f));
		bb->addPoint(Vector2(0.0f, 60.0f));
		bb->addPoint(Vector2(-20.0f, 40.0f));
		bb->addPoint(Vector2(-20.0f, 20.0f));
		// Last point is added again for the algorithm to work
		bb->addPoint(Vector2(0.0f, 0.0f));

		obj->setBoundBox(bb);
	}

	_map->objects.push_back(obj);
}
