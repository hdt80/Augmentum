#pragma once

#include "lua/LuaConfigEntry.h"

#include <SFML/Graphics.hpp>

class ParticleDef : public LuaConfigEntry {
public:
	// Ctor and dtor ///////////////////////////////////////////////////////////
	
	// ParticleDef ctor
	//
	// table - Table to load all the values from. The table can have the
	//		follwing values. If any value is not specified the default value
	//		is loaded.
	//
	//		NOTE: A color table is a sub table from the table passed in which is
	//		used to represent a sf::Color. A color table will look for the
	//		values of RGBA, with ints from 0 to 255. If any of the RGBA values
	//		are not found, a default value of 0 will be assumed.
	//
	//		lifetime: float - How many seconds the Particles created will last
	//		coneOfDispersion: float - How many degrees from the initial angle
	//			the Particles will will move from
	//		speedVariation: float - How far from the initial speed value the
	//			particles will move, either plus or minus
	//		initColor: color table - Initial color the Particles will be
	//		endColor: color table - Color the Particles will be before removal
	//		fade: bool - If the Particles will slowly fade to completely
	//			transparent just before removal
	//		speed: float - How many pixels per second the Particles will move
	//		slowDown: bool - If the Particles will slow down to 0 the closer
	//			they get to removal
	//
	ParticleDef(const sol::table& table);

	// Nullary ctor required for Databases. Default values of 0.0f will be
	//		loaded for floats, sf::Color::Transparent for sf::Colors and false
	//		for any bool values
	//
	ParticleDef();

	// Methods /////////////////////////////////////////////////////////////////
	
	// Load all the value from a sol::table, the table should have the same
	//		name as _name
	//
	// table - Table to load the values from
	//
	virtual void readFromTable(const sol::table& table);

	// Getters /////////////////////////////////////////////////////////////////
	
	// Get how many seconds the Particles will last for
	//
	// returns: _lifetime
	//
	inline float getLifetime() const { return _lifetime; }

	// Get how many degrees from the original degree the Particles will travel
	//
	// returns: _coneOfDispersion
	//
	inline float getConeOfDispersion() const { return _coneOfDispersion; }

	// Get the variation of speed from the original speed
	//
	// returns: _speedVariation
	//
	inline float getSpeedVariation() const { return _speedVariation; }

	// Get the initial color the Particles will be drawn
	//
	// returns: _initColor
	//
	inline const sf::Color& getInitColor() const { return _initColor; }

	// Get the color the Particles will be drawn before removal
	//
	// returns: _endColor
	//
	inline const sf::Color& getEndColor() const { return _endColor; }

	// Check if the Particles will fade over time till completely transparent
	//
	// returns: _fade
	//
	inline bool isFade() const { return _fade; }

	// Get the pixels per second the Particles will travel
	//
	// returns: _speed
	//
	inline float getSpeed() const { return _speed; }

	// Check if the Particles will slow down
	//
	// returns: _slowDown
	//
	inline bool isSlowDown() const { return _slowDown; }

protected:
	// Vars ////////////////////////////////////////////////////////////////////
	
	// How many seconds this particle will last for
	float _lifetime;

	// When given an angle to emit from how much varience will there be?
	float _coneOfDispersion;
	float _speedVariation; // How much faster or slow to go

	sf::Color _initColor; // What color the particles will start with
	sf::Color _endColor; // What color the particles will be just before removal
	bool _fade; // If the particles will fade the longer they're around

	float _speed; // How many pixels/second the particle will move from origin
	bool _slowDown; // If the particles should slow down to 0 as they update
};
