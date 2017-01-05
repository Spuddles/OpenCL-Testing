#include "GreyScale.h"

GreyScale::GreyScale()
{
}

GreyScale::~GreyScale()
{
}

bool GreyScale::initialise()
{
	return true;
}

bool GreyScale::run(RGBA *input, RGBA *output)
{
	for (int i = 0; i < 640 * 400; i++)
	{
		RGBA rgba = (*input++);
		int grey = (rgba.R + rgba.G + rgba.B)/3;
		rgba.A = 255;
		rgba.R = grey;
		rgba.G = grey;
		rgba.B = grey;
		*(output++) = rgba;
	}
	return true;
}

std::string	GreyScale::getName()
{
	return "GreyScale";
}
