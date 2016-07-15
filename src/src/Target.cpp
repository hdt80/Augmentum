#include "Target.h"
#include <cmath>

float Target::distanceWith(Target* target) {
	return distanceWith(target->getX(), target->getY());
}

float Target::distanceWith(float dx, float dy) {
	return std::sqrt((x - dx) * (x - dx) + (y - dy) * (y - dy));
}

float Target::distanceWithSqr(Target* target) {
	return distanceWithSqr(target->getX(), target->getY());
}

float Target::distanceWithSqr(float dx, float dy) {
	return ((x - dx) * (x - dx) + (y - dy) * (y - dy));
}
