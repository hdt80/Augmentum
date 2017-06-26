#include "util/UtilMath.h"

#include "util/UtilRandom.h"

#include "logger/Logger.h"

namespace ag {

namespace Math {

	int linearInterpolate(float max, float cur, float dt) {
		return max * (1 - dt) + cur * dt;
	}

	std::vector<Vec2f> generatePolygon(int sides, float size) {
		std::vector<Vec2f> points(sides);

		// Radians between each point
		float diff = PI / ((float) sides / 2.0f);

		// Define the points in a counter-clock wise manner
		for (int i = 0; i < sides; ++i) {
			points[i] = Vec2f(size * sin(diff * i), size * cos(diff * i));
		}

		return points;
	}

	std::vector<Vec2f> generateConvexPolygon(int sides, float size) {
		if (sides < 3) {
			AG_WARN("Generating a convex polygon requires at least 3 sides!");
			AG_WARN("Setting sides to 3");
			sides = 3;
		}
		// Vector of points to use
		std::vector<Vec2f> points(sides);

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
				points[i] = Vec2f(xside * sin(diff * i),
						yside * cos(diff * i));
			}
			++iter;
		} while (!isValidConvexPolygon(points));

		AG_DEBUG("Iterations: %d to create a convex polygon", iter);

		return points;
	}

	// Answer adaped from Uri Goren on Stackoverflow
	// https://stackoverflow.com/questions/471962
	bool isValidConvexPolygon(const std::vector<Vec2f>& points) {
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

	float getAngle(const Vec2f& v1, const Vec2f& v2, const Vec2f& v3) {

		// Length vec of v1 to v2
		Vec2f v12 = v1 - v2;

		// Length vec of v3 to v1
		Vec2f v31 = v3 - v1;

		float dot = v12.x * v31.x + v12.y * v31.y;
		float cross = v12.x * v31.y - v12.y * v31.x;

		return atan2(cross, dot);
	}

}; // namespace ag::Math

}; // namespace ag
