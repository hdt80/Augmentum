#ifndef _RANDOM_H_
#define _RANDOM_H_

namespace Random {
	// // Return a random number between, inclusive of, min and max
	// int randInt(int min, int max) {
	// 	return rand() % (max - min + 1) + min;
	// }

	// // Return a random number inside number, with each value corresponding to
	// // the same index value in weights. Weights are in percentages, 0.5 = 50%
	// // number = {1, 2, 3}, weights = {0.5, 0.2, 0.1}
	// // 1 has a 50% chance
	// // 2 has a 20% chance
	// // 3 has a 10% chance
	// int randWeightedInt(double n[], double w[], size_t nSize, size_t wSize)  {
	// 	std::vector<int> queue;
	// 	for (unsigned int i = 0; i < wSize; ++i) {
	// 		for (int j = 0; j < w[i] * 10; ++j) {
	// 			queue.push_back(n[i]);
	// 		}
	// 	}
	// 	//int i = randInt(0, queue.size() - 1);
	// 	std::random_shuffle(queue.begin(), queue.end());
	// 	return (queue[randInt(0, queue.size() - 1)]);
	// }
	int randInt(int min, int max);
	int randWeightedInt(double n[], double w[], int size);
}
#endif