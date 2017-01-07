#include "Nearest.h"
#include <algorithm>
#include <sstream>
#include "../Utils//Utils.h"

Nearest::Nearest()
{
}

Nearest::~Nearest()
{
}

bool Nearest::initialise()
{
	// Load in the charset
	m_CharSet = Utils::loadBinaryFile("..//Images//Charset-ordered.data");
	if (!m_CharSet)
		return false;

	return true;
}

int Nearest::findClosest(char *image)
{
	int bestScore = 0;
	int bestOffset = -1;
	for (int i = 0; i < 256; i++)
	{
		int score = 0;
		char *letter = &m_CharSet[i * 64];
		for (int c = 0; c < 64; c++)
		{
			int pixel = *(image++) + *(image++) + *(image++);
			if (pixel > 128) pixel = 1; else pixel = 0;
			if (pixel == *(letter))
			{
				score++;
			}
			else
			{
				score--;
			}
			image++;
		}
		if (abs(score) > bestScore)
		{
			bestScore = abs(score);
			bestOffset = i;
		}
	}
	return bestOffset;
}

bool Nearest::convert(RGBA *input, CHAR_INFO *output)
{
	for (int i = 0; i < 80*50; i++)
	{
		char image[8 * 8] = { 0 };

		int x = i % 80;
		int y = i / 80;

		// First extract the char we want to process
		Utils::extractFromImage((char*)input, 640, 400, image, 8, 8, x, y);

		// Now look for the closest char to it
		int closest = findClosest(image);

		output->Char.AsciiChar = closest;
		output->Attributes = 0x15;
		output++;
	}
	return true;
}

std::string	Nearest::getName()
{
	return "Nearest";
}
