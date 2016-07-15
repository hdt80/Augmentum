#ifndef _TRAIT_H
#define _TRAIT_H

class Trait {
	Trait();
	~Trait();

	bool freeze;	// On collision freeze the other object
	bool explosive; // On remove, remove all objects inside range
	bool healing;	// On remove, add health to all objects
};

#endif