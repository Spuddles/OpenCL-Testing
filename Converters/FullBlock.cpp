#include "FullBlock.h"
#include <algorithm>
#include <sstream>
#include "Utils.h"
#include "Structs.h"

FullBlock::FullBlock()
{
}

FullBlock::~FullBlock()
{
}

bool FullBlock::initialise()
{
	return Converter::initialise();
}

unsigned char FullBlock::getMainColour(RGBA *image)
{
	int r{ 0 }, g{ 0 }, b{ 0 };
	for (int i = 0; i < 64; i++)
	{
		RGBA &rgb = *image;
		r += rgb.R;
		g += rgb.G;
		b += rgb.B;
		image++;
	}

	RGBA colour;
	colour.R = r / 64;
	colour.G = g / 64;
	colour.B = b / 64;

	return getConsoleColour(colour);
}

bool FullBlock::convert(RGBA *input, CHAR_INFO *output)
{
	for (int i = 0; i < 80*50; i++)
	{
		RGBA image[8 * 8];

		int x = i % 80;
		int y = i / 80;

		// First extract the char we want to process
		Utils::extractFromImage((char*)input, 640, 400, (char*)image, 8, 8, x, y);

		char colour = getMainColour(image);

		output->Char.AsciiChar = 219;
		output->Attributes = colour;

		output++;
	}
	return true;
}

std::string	FullBlock::getName()
{
	return "FullBlock";
}
