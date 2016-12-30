#ifndef _UNIT_STATS_COMPONENT_H
#define _UNIT_STATS_COMPONENT_H

#include "gui/GuiComponent.h"

class Map;
class Unit;

class UnitStatsComponent : public GuiComponent {
public:

	// UnitStatsComponent ctor
	// window - Window this GuiComponent is being drawn to
	// entryStyle - How to draw the GuiEntries in this GuiComponent
	// compStyle - How to draw the background of this GuiComponent
	// pos - Where on the screen this component should start (pixels)
	// size - How much of the screen this component takes up (pixels)
	UnitStatsComponent(Window* window, const GuiEntryStyle* style,
			const GuiComponentStyle* compStyle, Vector2 pos, Vector2 size);		

	// Methods /////////////////////////////////////////////////////////////////

	// Update this component based on how many microseconds have passed
	// diff - Microseconds from the last update
	virtual void update(int diff);

	// Inherited from sf::Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Unit* _hovered; // Unit the mouse is hovering over

	Map* _map; // Map to get the Units off of

	GuiEntry* _unitPos; // Position of the Unit
	GuiEntry* _unitVelocity; // Current velocity of the Unit
	GuiEntry* _unitLevel; // Level/Exp of the Unit
	GuiEntry* _unitSpeed; // Stat speed of the Unit
	GuiEntry* _unitRange; // Stat range of the Unit
	GuiEntry* _unitDamage; // Stat damage of the Unit
	GuiEntry* _unitFireRate; // Stat FireRate of the Unit
	GuiEntry* _unitAccel; // Stat accel of the Unit
	GuiEntry* _unitProjSpeed; // Stat projSpeed of the Unit
	GuiEntry* _unitName; // If the Unit is an enemy, show the name as well
	GuiEntry* _unitHp; // Current health of unit
	GuiEntry* _unitMaxHp; // Max health of unit
};

#endif
