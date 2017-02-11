#ifndef _DATABASES_H
#define _DATABASES_H

#include "Database.h"

#include <SFML/Graphics.hpp>
#include "gui_style/GuiEntryStyle.h"
#include "gui_style/GuiComponentStyle.h"
#include "gui_style/GuiProgressBarStyle.h"
#include "ParticleEmitter.h"
#include "EnemyType.h"

// Global Databases that are used by lots of classes
namespace Databases {
	extern Database<sf::Font> Fonts;
	extern Database<GuiEntryStyle> GuiEntryStyles;
	extern Database<GuiComponentStyle> GuiComponentStyles;
	extern Database<GuiProgressBarStyle> GuiProgressBarStyles;
	extern Database<ParticleDef> ParticleDefs;
	extern Database<EnemyType> EnemyTypes;
};

#endif
