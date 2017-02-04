#pragma once
#include "Effect.h"

class BlackAndWhite :
	public Effect
{
public:
	BlackAndWhite();
	~BlackAndWhite();

	bool		initialise();
	bool		run(RGBA *input, RGBA *output);
	std::string	getName();
};

