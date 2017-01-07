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
	std::string	getName();

private:
	int			findClosest(char *image);

	char		*m_CharSet;
};

