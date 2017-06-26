#include "util/Vec3.h"
#include "util/Vec2.h"
#include "util/UtilRandom.h"

#include "logger/Logger.h"

int main() {

	SINFO("Testing Vec2i");

	ag::Vec2i vecia;
	ag::Vec2i vecib(-4, 5);

	// Testing addition
	ag::Vec2i vecir = vecia + vecib;
	SINFO("a + b = (%d, %d)\t\t\t\tShould be (-4, 5)", vecir.x, vecir.y);

	vecir = vecia - vecib;
	SINFO("a - b = (%d, %d)\t\t\t\tShould be (4, -5)", vecir.x, vecir.y);

	vecir += vecib;
	SINFO("r += b; (%d, %d)\t\t\t\tShould be (0, 0)", vecir.x, vecir.y);

	vecir += vecia;
	SINFO("r += a; (%d, %d)\t\t\t\tShould be (0, 0)", vecir.x, vecir.y);

	vecir = ag::Vec2i(4, 4);
	SINFO("r = (4, 4); (%d, %d)\t\t\tShould be (4, 4)", vecir.x, vecir.y);

	vecir = vecib * 2;
	SINFO("b * 2 = (%d, %d)\t\t\t\tShould be (-8, 10)", vecir.x, vecir.y);

	vecir *= 3;
	SINFO("r *= 3; (%d, %d)\t\t\tShould be (-24, 30)", vecir.x, vecir.y);

	vecir /= 6;
	SINFO("r /= 6; (%d, %d)\t\t\t\tShould be (-4, 5)", vecir.x, vecir.y);

	SINFO("a == b (%d)\t\t\t\tShould be 0", vecia == vecib);

	SINFO("a != b (%d)\t\t\t\tShould be 1", vecia != vecib);

	SINFO("");
	SINFO("");
	SINFO("");
	SINFO("");
	SINFO("");
	SINFO("");

	SINFO("Testing Random");

	SINFO("Testing initalized check");

	if (ag::Random::randInt(1, 10) == 0) {
		SINFO("Uninitalized check good");
	} else {
		SWARN("Uninitalized check bad");
	}

	SINFO("Seeding with 0");
	ag::Random::Seed(0);

	SINFO("Random::randInt testing:");
	for (unsigned int i = 0; i < 100; ++i) {
		SINFO("\t%d", ag::Random::randInt(0, i));
	}
	

	return 0;
}
