#ifndef _DEBUG_DRAW_H
#define _DEBUG_DRAW_H

#include <box2d/Box2d.h>
#include <SFML/Graphics.hpp>

class DebugDrawer : public b2Draw {
public:
	DebugDrawer();

	// Set the RenderWindow
	void setRenderWindow(sf::RenderWindow* window) { _window = window; }
	sf::RenderWindow* getRenderWindow() { return _window; }

	void setRenderTarget(sf::RenderTarget* target) { _target = target; }

	// Methods that b2DebugDraw uses to draw all the b2Bodies
	
	// Draw a closed polygon with points provided in a CCW order
	void DrawPolygon(const b2Vec2* vert, int vertCount, const b2Color& color);

	// Draw a solid closed polygon with points provided in a CCW order
	void DrawSolidPolygon(const b2Vec2* vert, int vertCount,
			const b2Color& color);

	// Draw a circle
	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);

	// Draw a solid circle
	void DrawSolidCircle(const b2Vec2& center, float rad,
			const b2Vec2& axix, const b2Color& color);

	// Draw a line segment
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	// Draw a transform
	void DrawTransform(const b2Transform& xf);

	// Draw a point
	void DrawPoint(const b2Vec2& p, float size, const b2Color& color);

protected:
	sf::RenderWindow* _window;
	sf::RenderTarget* _target;

	inline sf::Color getSfColor(const b2Color& color);
};

#endif
