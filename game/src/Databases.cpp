#include "game/Databases.h"

// Databases that are used by a lot of classes
namespace Databases {
	Database<sf::Font> Fonts;
	Database<GuiEntryStyle> GuiEntryStyles;
	Database<GuiComponentStyle> GuiComponentStyles;
	Database<GuiProgressBarStyle> GuiProgressBarStyles;
	Database<ParticleDef> ParticleDefs;
	Database<EnemyType> EnemyTypes;
}
