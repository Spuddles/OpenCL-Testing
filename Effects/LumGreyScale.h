#pragma once
#include "Effect.h"

class LumGreyScale :
	public Effect
{
public:
	LumGreyScale();
	~LumGreyScale();

	bool		initialise();
	bool		run(RGBA *input, RGBA *output);
	std::string	getName();
};

