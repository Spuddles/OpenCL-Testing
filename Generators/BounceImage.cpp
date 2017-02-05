#include "BounceImage.h"
#include "../Utils/Utils.h"

BounceImage::BounceImage()
{
}

BounceImage::~BounceImage()
{
}

bool BounceImage::initialise()
{
	m_ImageData = (RGBA*)Utils::loadBinaryFile("../Images/BW-Alien.data");
	return (m_ImageData != nullptr);
}

bool BounceImage::run(float time, RGBA *output)
{
	// Clear the bitmap
	RGBA	rgba{ 0,0,0,255 };
	for (int i = 0; i < 640 * 400; i++)
	{
		output[i] = rgba;
	}

	// Work out position of image over time
	static int x = 0;
	static int y = 0;
	static int dx = 1;
	static int dy = 1;

	x += dx;
	y += dy;

	if (x > 640 - 32)
	{
		x = 640 - 32;
		dx = -1;
	}
	else if (x < 0)
	{
		x = 0;
		dx = 1;
	}

	if (y > 400 - 32)
	{
		y = 400 - 32;
		dy = -1;
	}
	else if (y < 0)
	{
		y = 0;
		dy = 1;
	}

	RGBA* image = m_ImageData;
	// Blit image into our bitmap
	for (int v = y; v < (y + 32); v++)
	{
		for (int u = x; u < (x + 32); u++)
		{
			output[(v * 640) + u] = *(image++);
		}
	}

	return true;
}

std::string	BounceImage::getName()
{
	return "Bounce Image";
}