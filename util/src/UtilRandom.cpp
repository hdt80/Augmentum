#include "util/UtilRandom.h"

#include "logger/Logger.h"

#include <random>

namespace ag {

namespace Random {

	void Seed(int seed) {
		srand(seed);
		initalized = true;
	}

	int randInt(int min, int max) {
		if (initalized == false) {
			AG_WARN("Random has not been seeded");
			return 0;
		}
		return rand() % (max - min + 1) + min;
	}

	float randFloat(float min, float max) {
		if (initalized == false) {
			AG_WARN("Random has not been seeded");
			return 0.0f;
		}
		float f = (float) rand() / RAND_MAX;
		return min + f * (max - min);
	}

	bool initalized = false;

}; // namespace Random

}; // namespace ag
