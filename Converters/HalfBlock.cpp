#include "HalfBlock.h"
#include <algorithm>
#include <sstream>
#include "Utils.h"
#include "Structs.h"

HalfBlock::HalfBlock()
{
}

HalfBlock::~HalfBlock()
{
}

bool HalfBlock::initialise()
{
	return Converter::initialise();
}

unsigned char HalfBlock::getMainColour(RGBA *image)
{
	int r{ 0 }, g{ 0 }, b{ 0 };
	for (int i = 0; i < 32; i++)
	{
		RGBA &rgb = *image;
		r += rgb.R;
		g += rgb.G;
		b += rgb.B;
		image++;
	}

	RGBA colour;
	colour.R = r / 32;
	colour.G = g / 32;
	colour.B = b / 32;

	return getConsoleColour(colour);
}

bool HalfBlock::convert(RGBA *input, CHAR_INFO *output)
{
	for (int i = 0; i < 80*50; i++)
	{
		RGBA image[8 * 4];

		int x = i % 80;
		int y = i / 80;

		// First extract the char we want to process
		Utils::extractFromImage((char*)input, 640, 400, (char*)image, 8, 4, x, y*2);
		char topColour = getMainColour(image);
		Utils::extractFromImage((char*) input, 640, 400, (char*) image, 8, 4, x, (y*2)+1);
		char bottomColour = getMainColour(image);

		if (topColour == bottomColour)
		{
			output->Char.AsciiChar = 219;
			output->Attributes = topColour;
		}
		else
		{
			output->Char.AsciiChar = 223;
			output->Attributes = topColour + (bottomColour << 4);
		}
		output++;
	}
	return true;
}

std::string	HalfBlock::getName()
{
	return "HalfBlock";
}
