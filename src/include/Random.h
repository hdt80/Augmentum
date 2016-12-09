#ifndef _RANDOM_H_
#define _RANDOM_H_

namespace Random {
	// Generate a random int between min and max, inclusively
	// min - Min value of the number
	// max - Max value of the number
	// returns: A randomly generated int between min and max, inclusively
	int randInt(int min, int max);

	// Randomly generate and int, each with its own weight
	// n - Numbers to be generated. This should be the same length as w
	// w - Weights, each index corresponds with the number in n
	// size - How many elements there are
	// returns: A randomly gnereated number with weights on each number
	int randWeightedInt(double n[], double w[], int size);

	// Generate a random float between min and max, inclusively
	// min - Min value of the number
	// max - Max value of the number
	// returns: A randomly generated float between min and max, inclusiively
	float randFloat(float min, float max);
}
#endif
