#include "Logger.h"

class Foo {
public:
	Foo(int a) : _a(a) {}
	
	inline int getA() const { SWARN("what what"); return _a; }

	int _a;
};

class Bar {
public:
	Bar(int b) : _b(b) {}
	
	inline int getB() const { AG_WARN("bar"); return _b; }

	int _b;
};

class ReallyLongAnnoyingClassNameThatIDontKnowWhyItsNeeded {
public:
	ReallyLongAnnoyingClassNameThatIDontKnowWhyItsNeeded(int a)
		: _a(a) { AG_DEBUG("A is %d", a); }

	inline int getTheReallyAnnoyingClassNamesValue(int whatwhat) const {
		AG_INFO("AAAAAA"); return _a; }

	inline void param(int a, int b, int c, const std::string& d) {
		AG_INFO("what de_heck");
	}

	int _a;
};

class Ship {
public:
	Ship(float x, float y, float z) {
		AG_INFO("(%g, %g, %g)", x, y, z);
	}
};

int main(int argc, char** argv) {

	int i = -5;
	float f = 19.56f;
	std::string s = "AG-Logging hey";

	fprintf(stderr, "\n\nAG_* testing\n");

	AG_DEBUG("i: %d, f: %g, s: %s", i, f, s.c_str());
	AG_INFO("i: %d, f: %g, s: %s", i, f, s.c_str());
	AG_WARN("i: %d, f: %g, s: %s", i, f, s.c_str());
	AG_ERROR("i: %d, f: %g, s: %s", i, f, s.c_str());
	AG_LOG("Generic tag", "i: %d, f: %g, s: %s", i, f, s.c_str());

	fprintf(stderr, "\n\nS* testing\n");

	SDEBUG("i: %d, f: %g, s: %s", i, f, s.c_str());
	SINFO("i: %d, f: %g, s: %s", i, f, s.c_str());
	SWARN("i: %d, f: %g, s: %s", i, f, s.c_str());
	SERROR("i: %d, f: %g, s: %s", i, f, s.c_str());
	SLOG("Generic tag", "i: %d, f: %g, s: %s", i, f, s.c_str());

	fprintf(stderr, "\n\nClass testing (Foo)\n");

	Foo a(10);
	Foo b(20);

	AG_INFO("Foo a.getA(): %d", a.getA());
	AG_WARN("Foo b.getA(): %d", b.getA());

	fprintf(stderr, "\n\nClass testing (Ship)\n\tConstructor\n");

	Ship ship(-10.0f, 5.0f, -1.23f);

	fprintf(stderr, "\n\nClass testing (Long name)\n");

	ReallyLongAnnoyingClassNameThatIDontKnowWhyItsNeeded d(-10);

	d.param(0, 0, 0, "");

	AG_DEBUG("long name.value(10): %d",
		d.getTheReallyAnnoyingClassNamesValue(10));

	return 0;
}
