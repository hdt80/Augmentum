#include "KeyboardState.h"

bool KeyboardState::isPressed(int keyCode) {
	return keystates[keyCode];
}

void KeyboardState::setPressed(int keyCode, bool pressed) {
	keystates[keyCode] = pressed;
}


bool KeyboardState::keystates[100];
