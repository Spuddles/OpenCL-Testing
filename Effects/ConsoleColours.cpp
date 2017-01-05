#include "ConsoleColours.h"

ConsoleColours::ConsoleColours()
{
}

ConsoleColours::~ConsoleColours()
{
}

bool ConsoleColours::initialise()
{
	return true;
}

bool ConsoleColours::run(RGBA *input, RGBA *output)
{
	for (int i = 0; i < 640 * 400; i++)
	{
		RGBA rgba = (*input++);





		*(output++) = rgba;
	}
	return true;
}

std::string	ConsoleColours::getName()
{
	return "Console Colours";
}
