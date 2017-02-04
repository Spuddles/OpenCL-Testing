#include "BlackAndWhite.h"

BlackAndWhite::BlackAndWhite()
{
}

BlackAndWhite::~BlackAndWhite()
{
}

bool BlackAndWhite::initialise()
{
	return true;
}

bool BlackAndWhite::run(RGBA *input, RGBA *output)
{
	for (int i = 0; i < 640 * 400; i++)
	{
		RGBA rgba = (*input++);
		int grey = (rgba.R + rgba.G + rgba.B);
		
		if (grey > 48)
			grey = 255;
		else
			grey = 0;

		rgba.A = 255;
		rgba.R = grey;
		rgba.G = grey;
		rgba.B = grey;
		*(output++) = rgba;
	}
	return true;
}

std::string	BlackAndWhite::getName()
{
	return "BlackAndWhite";
}
