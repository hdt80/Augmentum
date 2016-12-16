#include "util/MathUtil.h"

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
}
