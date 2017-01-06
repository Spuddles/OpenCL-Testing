#pragma once
#include "Effect.h"

class Fade :
	public Effect
{
public:
	Fade(int offset);
	~Fade();

	bool		initialise();
	bool		run(RGBA *input, RGBA *output);
	std::string	getName();
private:
	int			m_Offset;
};

