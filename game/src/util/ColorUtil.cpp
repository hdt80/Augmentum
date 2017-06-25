#include "game/util/ColorUtil.h"

#include "game/util/MathUtil.h"

namespace ColorUtil {

	sf::Color colorInterpolate(sf::Color min, sf::Color max, float t) {
		// Create HSVColors of the min and max
		HSVConvert::HSVColor hmin = HSVConvert::RGBToHSV(min.r, min.g, min.b);
		HSVConvert::HSVColor hmax = HSVConvert::RGBToHSV(max.r, max.g, max.b);

		// Interpolated color
		HSVConvert::HSVColor done;

		// Interpolate each component
		done.h = MathUtil::linearInterpolate(hmin.h, hmax.h, t);
		done.s = MathUtil::linearInterpolate(hmin.s, hmax.s, t);
		done.v = MathUtil::linearInterpolate(hmin.v, hmax.v, t);

		// Convert the interpolated HSVColor into a sf::Color
		return HSVConvert::HSVToRGB(done.h, done.s, done.v);
	}

	namespace HSVConvert {

		// Credit to David H on Stackoverflow for finding this, and credit
		// to who ever originally wrote this
		// https://stackoverflow.com/questions/3018313/
		HSVColor RGBToHSV(double r, double g, double b) {
			HSVColor out;
			double min, max, delta;

			min = r < g ? r : g;
			min = min < b ? min : b;

			max = r > g ? r : g;
			max = max  > b ? max : b;

			out.v = max; // v
			delta = max - min;

			if (delta < 0.00001) {
				out.s = 0;
				out.h = 0; // undefined, maybe nan?
				return out;
			}

			// NOTE: if Max is == 0, this divide would cause a crash
			if (max > 0.0 ) {
				out.s = (delta / max); // s
			} else {
				// if max is 0, then r = g = b = 0
				// s = 0, v is undefined
				out.s = 0.0;
				out.h = 9e99; // its now undefined
				return out;
			}

			if (r >= max) {
				out.h = (g - b) / delta;
			} else if (g >= max) {
				out.h = 2.0 + (b - r) / delta;
			} else {
				out.h = 4.0 + (r - g) / delta;
			}

			out.h *= 60.0;

			if (out.h < 0.0 ) {
				out.h += 360.0;
			}

			return out;
		}

		// Credit to David H on Stackoverflow for finding this, and credit
		// to who ever originally wrote this
		// https://stackoverflow.com/questions/3018313/
		sf::Color HSVToRGB(double h, double s, double v) {
			double  hh, p, q, t, ff;
			long i;
			sf::Color out;

			if (s <= 0.0) { // < is bogus, just shuts up warnings
				out.r = v;
				out.g = v;
				out.b = v;
				return out;
			}

			hh = h;

			if (hh >= 360.0) {
				hh = 0.0;
			}

			hh /= 60.0;
			i = (long) hh;
			ff = hh - i;

			p = v * (1.0 - s);
			q = v * (1.0 - (s * ff));
			t = v * (1.0 - (s * (1.0 - ff)));

			switch(i) {
				case 0:
					out.r = v;
					out.g = t;
					out.b = p;
					break;
				case 1:
					out.r = q;
					out.g = v;
					out.b = p;
					break;
				case 2:
					out.r = p;
					out.g = v;
					out.b = t;
					break;
				case 3:
					out.r = p;
					out.g = q;
					out.b = v;
					break;
				case 4:
					out.r = t;
					out.g = p;
					out.b = v;
					break;
				case 5:
				default:
					out.r = v;
					out.g = p;
					out.b = q;
					break;
			}
			return out;
		}
	}
};
