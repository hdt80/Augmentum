#include "Colors.h"

namespace ConsoleColors {
	const char clear[] =   { 0x1b, '[', '0', '3', '0', 'm', 0};
	const char reset[] =   { 0x1b, '[', '0', '3', '9', 'm', 0};
	const char red[] =     { 0x1b, '[', '0', '3', '1', 'm', 0};
	const char green[] =   { 0x1b, '[', '0', '3', '2', 'm', 0};
	const char yellow[] =  { 0x1b, '[', '0', '3', '3', 'm', 0};
	const char blue[] =    { 0x1b, '[', '0', '3', '4', 'm', 0};
	const char magenta[] = { 0x1b, '[', '0', '3', '5', 'm', 0};
	const char cyan[] =    { 0x1b, '[', '0', '3', '6', 'm', 0};
	const char white[] =   { 0x1b, '[', '0', '3', '7', 'm', 0};
}
