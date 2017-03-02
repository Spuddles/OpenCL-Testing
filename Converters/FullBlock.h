#pragma once
#include "Converter.h"

class FullBlock :
	public Converter
{
public:
	FullBlock();
	~FullBlock();

	bool		initialise();
	bool		convert(RGBA *input, CHAR_INFO *output);

	std::string	getName();

private:
	unsigned char	getMainColour(RGBA *image);
};

