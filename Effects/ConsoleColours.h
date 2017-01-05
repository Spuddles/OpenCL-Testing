#pragma once
#include "Effect.h"

class ConsoleColours :
	public Effect
{
public:
	ConsoleColours();
	~ConsoleColours();

	bool		initialise();
	bool		run(RGBA *input, RGBA *output);
	std::string	getName();
};

