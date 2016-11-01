#ifndef _BIT_WISE_H
#define _BIT_WISE_H

namespace BitWise {

	// Turn on a bit
	// flag - Flag to turn the bit on
	// option - Bit to turn on
	// returns: Flag with the option on
	int bitOn(int flag, int option);

	// Turn off a bit
	// flag - Flag to turn the bit off
	// option - Bit to turn off
	// returns: Flag with the option off
	int bitOff(int flag, int option);

	// Toggle a bit between on and off
	// flag - Flag to toggle the bit on
	// option - Bit to toggle
	// returns: Flag with the bit toggled
	int bitToggle(int flag, int option);

	// See if a option is on
	// flag - Flag to query
	// option - Option to check for
	// returns: If the flag is the option set to on
	bool bitSet(int flag, int option);

};

#endif
