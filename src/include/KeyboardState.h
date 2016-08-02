#ifndef _KEYBOARD_STATE_H
#define _KEYBOARD_STATE_H

class KeyboardState {
public:

	static bool isPressed(int keyCode);
	static void setPressed(int keyCode, bool pressed);

private:
	static bool keystates[100];

};

#endif
