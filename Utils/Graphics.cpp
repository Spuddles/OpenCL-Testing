#include "Graphics.h"
#include <cassert>

Graphics::Graphics(unsigned int width, unsigned int height):
	m_Width(width)
	,m_Height(height)
{
}

Graphics::~Graphics()
{
}

void Graphics::setBitmap(RGBA *bitmap)
{
	m_Bitmap = bitmap;
}

void Graphics::setColour(RGBA rgb)
{
	m_DefaultColour = rgb;
}

void Graphics::clear()
{
	RGBA rgba{ 0,0,0,255 };
	for (int i = 0; i < (m_Width*m_Height); i++)
	{
		m_Bitmap[i] = rgba;
	}
}

void Graphics::setPixel(unsigned int x, unsigned int y)
{
	unsigned int offset = (y*m_Width) + x;
	assert(offset < m_Width*m_Height);

	m_Bitmap[offset] = m_DefaultColour;
}

void Graphics::setPixel(unsigned int x, unsigned int y, RGBA rgb)
{
	unsigned int offset = (y*m_Width) + x;
	assert(offset < m_Width*m_Height);

	m_Bitmap[offset] = rgb;
}

void Graphics::drawLine(int x1, int y1
	, int x2, int y2)
{
	drawLine(x1, y1, x2, y2, m_DefaultColour);
}

void Graphics::drawLine(int x1, int y1
	, int x2, int y2, RGBA rgb)
{
	float dx = x2 - x1;
	float dy = y2 - y1;

	// We want to process the longest dimention of the line
	if (abs(dx) > abs(dy))
	{
		if (x1 > x2)
		{
			// Flip the co-ords so we can process left to right
			unsigned int t = x1;
			x2 = x1; x1 = t;
			t = y1; y1 = y2; y2 = t;
		}

		// Move along the x axis to draw
		for (unsigned int x = x1; x < x2; x++)
		{
			int y = y1 + (dy*((x - x1) / dx));
			setPixel(x, y, m_DefaultColour);
		}
	}
	else
	{
		if (y1 > y2)
		{
			// Flip the co-ords so we can process top to bottom
			unsigned int t = x1;
			x2 = x1; x1 = t;
			t = y1; y1 = y2; y2 = t;
		}

		// Move along the y axis to draw
		for (unsigned int y = y1; y < y2; y++)
		{
			int x = x1 + (dx*((y - y1) / dy));
			setPixel(x, y, m_DefaultColour);
		}
	}
}

void Graphics::drawLines(std::vector<std::pair<unsigned int, unsigned int>> points)
{

}
