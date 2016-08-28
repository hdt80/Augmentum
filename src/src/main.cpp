// =================================
// Includes
// =================================
#define DO_DEBUG

#include <stdlib.h>
#include <random>

#include "Logger.h"

#include "Game.h"

#include "Convert.h"

// =================================
// Main
// =================================
int main(int argc, char* argv[]) {
	srand(time(0));
	Logger::instance().setLogFile("log.html", false, true);

	CORE_INFO("Current working directory %s", convert::getWorkingDir().c_str());

   	Game::start();
	return 0;
}
