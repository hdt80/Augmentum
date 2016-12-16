#include <random>
#include <vector>
#include <algorithm>

#include "util/Random.h"

namespace Random {
	int randInt(int min, int max) {
		return rand() % (max - min + 1) + min;
	}

	int randWeightedInt(double n[], double w[], int size)  {
		std::vector<int> queue;
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < w[i] * 10; ++j) {
				queue.push_back(n[i]);
			}
		}
		std::random_shuffle(queue.begin(), queue.end());
		return (queue[randInt(0, queue.size() - 1)]);
	}

	float randFloat(float min, float max) {
		float f = (float) rand() / RAND_MAX;
		return min + f * (max - min);
	}
};
