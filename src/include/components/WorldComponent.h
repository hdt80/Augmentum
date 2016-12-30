#ifndef _WORLD_COMPONENT_H
#define _WORLD_COMPONENT_H

#include "gui/GuiComponent.h"

class Map;

class WorldComponent : public GuiComponent {
public:
	WorldComponent(Window* window, const GuiEntryStyle* style,
			const GuiComponentStyle* compStyle, Vector2 pos, Vector2 size);		

	virtual void update(int diff);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void onClick(int button, float window_x, float window_y,
						 float view_x, float view_y);

	// 
	void setDrawBounds(bool b) { _drawBounds = b; }
	bool getDrawBounds() const { return _drawBounds; }
private:
	bool _drawBounds; // Draw the bounding boxes of the Objects

	Map* _map;
};

#endif
