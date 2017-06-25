#include "game/Game.h"

#include "game/util/StringUtil.h"

#include "logger/Logger.h"

#include <Box2D/Box2D.h>

#include <stdlib.h>
#include <random>

// Enabling colored output on Windows 10
#ifdef _WIN32
#include <windows.h>

// By defining the method in this macro we can ensure that it doesn't exist
// outside of Windows
void setColorOutput();

// Because I'm too lazy to update my WinSDK, we manually define what 
// ENABLE_VIRTUAL_TERMINAL_PROCESSING is so we can use colored output
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
	#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif // ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING

#endif // _WIN32

////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {

#	ifdef _WIN32
	setColorOutput();
#	endif // _WIN32

	// Seed the rng from the current time
	srand(time(0));

	AG_INFO("Box2D version: %d.%d.%d",
		b2_version.major, b2_version.minor, b2_version.revision);

	AG_INFO("Running from: %s", StringUtil::getWorkingDir().c_str());

	// Start the game
   	Game::start();

	return 0;
}

#ifdef _WIN32
// In Windows 10 Microsoft finally added support for UNIX esc chars, so the
// flag to use UNIX esc chars is enabled
// If you're not using the Windows 10 update that added support for this then
// you'll have ugly output
void setColorOutput() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) {
		AG_ERROR("INVALID_HANDLE_VALUE: %d", GetLastError());
		return;
	}

	DWORD consoleMode = 0;
	if (!GetConsoleMode(hOut, &consoleMode)) {
		AG_ERROR("GetConsoleMode failed: %d", GetLastError());
		return;
	}

	consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, consoleMode)) {
		AG_ERROR("SetConsoleMode failed: %d", GetLastError());
		return;
	}
}
#endif // _WIN32
