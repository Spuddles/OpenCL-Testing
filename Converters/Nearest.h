#pragma once
#include "Converter.h"

class Nearest :
	public Converter
{
public:
	Nearest();
	~Nearest();

	bool		initialise();
	bool		convert(RGBA *input, CHAR_INFO *output);
	bool		convertBack(CHAR_INFO *input, RGBA *output);

	std::string	getName();

private:
	int			findClosestColour(unsigned char *image);
	int			findClosestChar(unsigned char *image);
	int			findConsoleColour(unsigned char *image);

	std::vector<unsigned char>	m_vecCharsToTest;
};

