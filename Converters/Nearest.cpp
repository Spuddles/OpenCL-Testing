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

int Nearest::findClosest(unsigned char *image)
{
	int bestScore = 0;
	int bestOffset = -1;
	for (int i = 0; i < 256; i++)
	{
		unsigned char *block = image;
		int score = 0;
		char *letter = &m_CharSet[i * 64];
		for (int c = 0; c < 64; c++)
		{
			int pixel = *(block++) + *(block++) + *(block++);
			if (pixel > 32) pixel = 1; else pixel = 0;
			if (pixel == *(letter++))
			{
				score++;
			}
			else
			{
				score--;
			}
			block++;
		}
		if (score > bestScore)
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
		RGBA image[8 * 8] = { 0 };

		int x = i % 80;
		int y = i / 80;

		// First extract the char we want to process
		Utils::extractFromImage((char*)input, 640, 400, (char*)image, 8, 8, x, y);

		// Now look for the closest char to it
		int closest = findClosest((unsigned char*)image);

		output->Char.AsciiChar = closest;
		output->Attributes = 0x15;
		output++;
	}
	return true;
}

bool Nearest::convertBack(CHAR_INFO *input, RGBA *output)
{
	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			int offset = (y * 80) + x;

			unsigned char c  = input[offset].Char.AsciiChar;
			unsigned char fg = input[offset].Attributes % 16;
			unsigned char bg = input[offset].Attributes / 16;
			char* fontdata = m_CharSet + (c * 64);

			for (int v = 0; v < 8; v++)
			{
				for (int u = 0; u < 8; u++)
				{
					RGBA *write = output + (y * 640 * 8) + (x * 8) + (v * 640) + u;
					if (*fontdata > 0)
					{
						write->R = 128;
						write->G = 128;
						write->B = 128;
						write->A = 255;
					}
					else
					{
						write->R = 0;
						write->G = 0;
						write->B = 0;
						write->A = 255;
					}
					fontdata++;
				}
			}
		}
	}
	return true;
}

std::string	Nearest::getName()
{
	return "Nearest";
}
