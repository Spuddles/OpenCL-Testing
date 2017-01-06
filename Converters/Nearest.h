#pragma once
#include "Converter.h"

class Nearest :
	public Effect
{
public:
	Nearest(int offset);
	~Nearest();

	bool		initialise();
	bool		convert(RGBA *input, unsigned char *output) = 0;
	std::string	getName();
};

