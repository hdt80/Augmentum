#pragma once

#include "game/Database.h"
#include "game/gui_style/GuiEntryStyle.h"
#include "game/gui_style/GuiComponentStyle.h"
#include "game/gui_style/GuiProgressBarStyle.h"
#include "game/ParticleDef.h"
#include "game/EnemyType.h"

#include <SFML/Graphics.hpp>

// Global Databases that are used by lots of classes
namespace Databases {
	extern Database<sf::Font> Fonts;
	extern Database<GuiEntryStyle> GuiEntryStyles;
	extern Database<GuiComponentStyle> GuiComponentStyles;
	extern Database<GuiProgressBarStyle> GuiProgressBarStyles;
	extern Database<ParticleDef> ParticleDefs;
	extern Database<EnemyType> EnemyTypes;
};
