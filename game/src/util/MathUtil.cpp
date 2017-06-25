#include "game/util/MathUtil.h"

#include "game/util/Random.h"

#include "logger/Logger.h"

#include <cmath>

namespace MathUtil {

	int linearInterpolate(float max, float cur, float dt) {
		return max * (1 - dt) + cur * dt;
	}

	std::vector<b2Vec2> generatePolygon(int sides, float size) {
		std::vector<b2Vec2> points(sides);

		// Radians between each point
		float diff = PI / ((float) sides / 2.0f);

		// Define the points in a counter-clock wise manner
		for (int i = 0; i < sides; ++i) {
			points[i] = b2Vec2(size * sin(diff * i), size * cos(diff * i));
		}

		return points;
	}

	std::vector<b2Vec2> generateConvexPolygon(int sides, float size) {
		if (sides < 3) {
			AG_WARN("Generating a convex polygon requires at least 3 sides!");
			AG_WARN("Setting sides to 3");
			sides = 3;
		}
		// Vector of points to use
		std::vector<b2Vec2> points(sides);

		// Radians between each point
		float diff = PI / ((float) sides / 2.0f);

		// Vars to store the length of each side
		float xside = 0.0f;
		float yside = 0.0f;

		int iter = 0; // Iterations to find a valid polygon
		float rat = 0.35f; // Diff ratio sides can be

		// Find the sides, and check that it forms a valid convex polygon,
		// if not do it till a valid convex polygon is generated
		do {
			for (int i = 0; i < sides; ++i) {
				xside = Random::randFloat(size - (rat * size),
					size + (rat * size));
				yside = Random::randFloat(size - (rat * size),
					size + (rat * size));
				points[i] = b2Vec2(xside * sin(diff * i),
					yside * cos(diff * i));
			}
			++iter;
		} while (!isValidConvexPolygon(points));

		AG_INFO("Iterations: %d", iter);

		return points;
	}

	// Answer adaped from Uri Goren on Stackoverflow
	// https://stackoverflow.com/questions/471962
	bool isValidConvexPolygon(const std::vector<b2Vec2>& points) {
		// 3 points make a triangle, can't make anything else
		if (points.size() == 3) {
			return true;
		}

		bool sign = false; // Direction of the polygon
		int len = points.size(); // Number of points
		float x1, y1, x2, y2; // Vertex points
		float cross; // Cross product of the 2 points

		for (int i = 0; i < len; ++i) {
			x1 = points[(i + 2) % len].x - points[(i + 1) % len].x;
			y1 = points[(i + 2) % len].y - points[(i + 1) % len].y;
			x2 = points[i].x - points[(i + 1) % len].x;
			y2 = points[i].y - points[(i + 1) % len].y;
			cross = x1 * y2 - y1 * x2;

			// Check the sign of the points, this way it doesn't matter if the
			// points are given in counter clockwise or clockwise order
			if (i == 0) {
				sign = (cross > 0);
			} else if (sign != (cross > 0)) {
				return false;
			}
		}

		return true;
	}

	int wrap(int val, int min, int max) {
		int range = max - min + 1;

		// If it's smaller wrap it over the max
		if (val < range) {
			val += range * ((min - val) / range + 1);
		}

		//return min + fmod(val - min, range);
		return min + (val - min) % range;
	}

	float approach(float max, float cur, float dt) {
		float diff = max - cur;

		if (diff > dt) {
			return cur + dt;
		}
		if (diff < -dt) {
			return cur - dt;
		}
		return max;
	}

	float getAngle(Vector2 v1, Vector2 v2, Vector2 v3) {
		Vector2 v21 = v1 - v2;
		Vector2 v31 = v3 - v2;

		float dot = v21.X * v31.X + v21.Y * v31.Y;
		float cross = v21.X * v31.Y - v21.Y * v31.X;

		return atan2(cross, dot);
	}
}
