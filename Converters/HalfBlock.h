#pragma once
#include "Converter.h"

class HalfBlock :
	public Converter
{
public:
	HalfBlock();
	~HalfBlock();

	bool		initialise();
	bool		convert(RGBA *input, CHAR_INFO *output);

	std::string	getName();

private:
	unsigned char	getMainColour(RGBA *image);
};

