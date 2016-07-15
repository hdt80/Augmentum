#ifndef _COLOR_H
#define _COLOR_H

#include <SFML/Graphics.hpp>

typedef unsigned char byte;

struct Color {
	Color(byte r, byte g, byte b, byte a) : 
		r(r), g(g), b(b), a(a) {}
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	sf::Color toSF() {
		return sf::Color(r, g, b, a);
	}
};

#endif