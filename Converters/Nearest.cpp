#include "Nearest.h"
#include <algorithm>
#include <sstream>

Nearest::Nearest()
{
}

Nearest::~Nearest()
{
}

bool Nearest::initialise()
{
	return true;
}

bool Nearest::convert(RGBA *input, unsigned char *output)
{
	for (int i = 0; i < 640 * 400; i++)
	{
		RGBA rgba = (*input++);
		*(output++) = rgba.A;
	}
	return true;
}

std::string	Nearest::getName()
{
	return "Nearest";
}
