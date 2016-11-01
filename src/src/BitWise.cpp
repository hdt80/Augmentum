#include "BitWise.h"

namespace BitWise {

	int bitOn(int flag, int option) {
		return flag |= option;
	}

	int bitOff(int flag, int option) {
		return flag &= ~option;
	}

	int bitToggle(int flag, int option) {
		return flag ^= option;
	}

	bool bitSet(int flag, int option) {
		return flag & option;
	}
};
