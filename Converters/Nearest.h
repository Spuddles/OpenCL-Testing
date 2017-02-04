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
	int			findClosest(unsigned char *image);

	char		*m_CharSet;
};

