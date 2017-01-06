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

bool Nearest::convert(RGBA *input, CHAR_INFO *output)
{
	for (int i = 0; i < 640 * 400; i++)
	{
		RGBA rgba = (*input++);
		output->Char.AsciiChar = '*';
		output++;
	}
	return true;
}

std::string	Nearest::getName()
{
	return "Nearest";
}
