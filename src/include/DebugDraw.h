#ifndef _DEBUG_DRAW_H
#define _DEBUG_DRAW_H

#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>

class DebugDrawer : public b2Draw {
public:
	DebugDrawer();

	// Set the RenderWindow
	void setRenderWindow(sf::RenderWindow* window) { _window = window; }
	sf::RenderWindow* getRenderWindow() { return _window; }

	// Methods that b2DebugDraw uses to draw all the b2Bodies
	
	// Draw a closed polygon with points provided in a CCW order
	// vert - Vertices to draw
	// vertCount - Number of verticies
	// color - Color to draw the polygon as
	void DrawPolygon(const b2Vec2* vert, int vertCount, const b2Color& color);

	// Draw a solid closed polygon with points provided in a CCW order
	// vert - Vertices to draw
	// vertCount - Number of verticies
	// color - Color to draw the polygon as
	void DrawSolidPolygon(const b2Vec2* vert, int vertCount,
			const b2Color& color);

	// Draw a circle
	// center - Center of the circle
	// radius - Radius of the circle to draw, in Box2D units
	// color - Color to draw the circle as
	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);

	// Draw a solid circle
	// center - Center of the circle
	// radius - Radius of the circle to draw, in Box2D units
	// color - Color to draw the circle as
	void DrawSolidCircle(const b2Vec2& center, float rad,
			const b2Vec2& axix, const b2Color& color);

	// Draw a line segment
	// p1 - Point one to draw from
	// p2 - Point to draw to
	// color - Color to draw the line as
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	// Draw a transform
	// xf - Transformation to draw
	void DrawTransform(const b2Transform& xf);

	// Draw a point
	// p - Point to draw
	// size - Size in pixels to draw the point as
	// color - Color to draw the point as
	void DrawPoint(const b2Vec2& p, float size, const b2Color& color);

protected:
	sf::RenderWindow* _window;

	inline sf::Color getSfColor(const b2Color& color);
};

#endif
