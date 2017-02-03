#pragma once
#include "Generator.h"

class ColourTest : public Generator
{
public:
	ColourTest();
	~ColourTest();

	virtual bool		initialise();
	virtual bool		run(float time, RGBA *output);
	virtual std::string	getName();
};

