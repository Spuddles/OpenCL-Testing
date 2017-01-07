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
	for (int i = 0; i < 80*50; i++)
	{
		// First extract the char we want to process

		// Now look for the closest char to it
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
