#ifndef _SMFL_UTIL_H
#define _SMFL_UTIL_H

#include "Vector2.h"

class Window;

namespace SFMLUtil {

	// Get the position of the mouse relative to a Window
	// mousex - X position of the mouse, relative to the top left of the game
	// mousey - Y position of the mouse, relative to the top left of the game
	// window - Window to get the click relative to
	Vector2 getRelativeMouseClick(float mousex, float mousey, Window* window);
};

#endif
