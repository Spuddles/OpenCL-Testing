#pragma once
#include "Effect.h"

class GreyScale :
	public Effect
{
public:
	GreyScale();
	~GreyScale();

	bool		initialise();
	bool		run(RGBA *input, RGBA *output);
	std::string	getName();
};

