#pragma once

namespace ag {

namespace Random {

// Seed the Random engine with a specific seed. This allows the other random
//		functions to be called, before this is called random numbers can not be
//		generated, and attempting to do so will return 0 everytime
//
// seed - Value to seed the Random engine with
//
void Seed(int seed);

// Get a random int between min and max inclusively [min, max]
//
// min - Minumum value of the random int
// max - Maximum value of the random int
//
// returns: A random int between min and max
//
int randInt(int min, int max);

// Get a random float between min and max inclusively [min, max]
//
// min - Minumum value of the random float
// max - Maximum value of the random float
//
// returns: A random float between min and max
//
float randFloat(float min, float max);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

// If Random has been seeded to a value. This will start as false, and while
// false, no random number can be generated. A call to ag::Random::Seed(int)
// is required to seed the initial value of the Random engine
extern bool initalized;

}; // namespace ag::Random

}; // namespace ag

