#include "ColourTest.h"

ColourTest::ColourTest()
{
}

ColourTest::~ColourTest()
{
}

bool ColourTest::initialise()
{
	return true;
}

bool ColourTest::run(float time, RGBA *output)
{
	// Fade a greyscale colour in
	RGBA	rgba;
	int grey = (int) (time * 25) % 255;
	rgba.R = grey;
	rgba.G = grey;
	rgba.B = grey;
	rgba.A = 255;

	for (int i = 0; i < 640 * 400; i++)
	{
		*(output++) = rgba;
	}
	return true;
}

std::string	ColourTest::getName()
{
	return "Colour Test";
}