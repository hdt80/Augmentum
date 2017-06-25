#include "game/DebugDraw.h"

#include "logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
// Ctor and dtor
////////////////////////////////////////////////////////////////////////////////

DebugDrawer::DebugDrawer() {}

////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////

// Get the sf::Color equivalent to the b2Color
sf::Color DebugDrawer::getSfColor(const b2Color& color) {
	return sf::Color(
		color.r * 255, color.g * 255, color.b * 255, color.a * 255);
}

void DebugDrawer::DrawPolygon(const b2Vec2* verts,
		int vertCount, const b2Color& color) {

	// Add one extra point to close the polygon
	sf::VertexArray aa(sf::LinesStrip, vertCount + 1);
	for (int i = 0; i < vertCount; ++i) {
		aa[i].position = sf::Vector2f(verts[i].x, verts[i].y);
		aa[i].color = getSfColor(color);
	}
	// Add the first point again to close the polygon
	aa[vertCount].position = sf::Vector2f(verts[0].x, verts[0].y);
	aa[vertCount].color = getSfColor(color);

	_window->draw(aa);
	
}

void DebugDrawer::DrawSolidPolygon(const b2Vec2* verts,
		int vertCount, const b2Color& color) {

	// One more to draw the line from the end to beginning
	sf::ConvexShape shape(vertCount + 1);
	shape.setFillColor(getSfColor(color));
	shape.setPosition(sf::Vector2f(verts[0].x, verts[0].y));

	for (int i = 0; i < vertCount; ++i) {
		shape.setPoint(i, sf::Vector2f(verts[i].x, verts[i].y));
	}
	shape.setPoint(vertCount, sf::Vector2f(verts[0].x, verts[0].y));

	_window->draw(shape);
}

void DebugDrawer::DrawCircle(const b2Vec2& center, float radius,
		const b2Color& color) {

	sf::CircleShape shape(radius);
	shape.setPosition(center.x, center.y);
	shape.setOutlineColor(getSfColor(color));
	shape.setOutlineThickness(-1.0f);
	shape.setFillColor(sf::Color::Transparent);

	_window->draw(shape);
}

void DebugDrawer::DrawSolidCircle(const b2Vec2& center,
		float radius, const b2Vec2& axis, const b2Color& color) {

	sf::CircleShape shape(radius);
	sf::Color col = getSfColor(color);
	shape.setPosition(center.x, center.y);
	shape.setOutlineColor(col);
	shape.setOutlineThickness(-1.0f);
	shape.setFillColor(col);

	// The Axis is which direction the circle faces
	b2Vec2 p = center + (radius * axis);
	sf::VertexArray aa(sf::Lines, 2);
	aa[0].position = sf::Vector2f(center.x, center.x);
	aa[0].color = col;
	aa[1].position = sf::Vector2f(p.x, p.y);
	aa[1].color = col;

	_window->draw(shape);
	_window->draw(aa);
}

void DebugDrawer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2,
		const b2Color& color) {

	sf::VertexArray aa(sf::Lines, 2);
	sf::Color col = getSfColor(color);
	aa[0].position = sf::Vector2f(p1.x, p1.x);
	aa[0].color = col;
	aa[1].position = sf::Vector2f(p2.x, p2.y);
	aa[1].color = col;

	_window->draw(aa);
}

void DebugDrawer::DrawTransform(const b2Transform& xd) {

//	AG_INFO("draw trans");
}

void DebugDrawer::DrawPoint(const b2Vec2& p,
		float size, const b2Color& color) {

//	AG_INFO("draw point");
	DrawCircle(p, size, color);
}
