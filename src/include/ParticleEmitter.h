#ifndef _PARTICLE_EMITTER_H
#define _PARTICLE_EMITTER_H

#include "GameWindow.h"

class Window;
struct Color;

namespace ParticleEmit {
	void emit(float x, float y, int amount, Color c);

	extern GameWindow* window;
};

#endif