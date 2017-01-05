#include "LumGreyScale.h"

LumGreyScale::LumGreyScale()
{
}

LumGreyScale::~LumGreyScale()
{
}

bool LumGreyScale::initialise()
{
	return true;
}

bool LumGreyScale::run(RGBA *input, RGBA *output)
{
	for (int i = 0; i < 640 * 400; i++)
	{
		RGBA rgba = (*input++);
		float lum = (0.2126f*rgba.R) + (0.7152f*rgba.G) + (0.0722f*rgba.B);
		int grey = (int)lum;
		rgba.A = 255;
		rgba.R = grey;
		rgba.G = grey;
		rgba.B = grey;
		*(output++) = rgba;
	}
	return true;
}

std::string	LumGreyScale::getName()
{
	return "Lum GreyScale";
}
