#pragma once

#include <SFML/Graphics.hpp>

namespace ColorUtil {

	// Interpolate between two colors
	// min - Min color, when t = 0
	// max - Max color, when t = 1
	// t - Percent to interpolate as in decimal form
	sf::Color colorInterpolate(sf::Color min, sf::Color max, float t);

	namespace HSVConvert {

		// Represents a HSVColor
		struct HSVColor {
			double h; // angle in degrees
			double s; // percent
			double v; // percent
		};

		// Convert an RGB color to an HSL
		// r - R value, percent
		// g - G value, percent
		// b - B value, percent
		// returns: The HSLColor equivalant
		HSVColor RGBToHSV(double r, double g, double b);

		// Convert an HSL Color to an RGB
		// h - Hue, angle in degrees
		// s - Saturation in percent
		// v - Value in percent
		sf::Color HSVToRGB(double h, double s, double v);

	};
};
