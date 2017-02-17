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

void Graphics::drawLine(unsigned int x1, unsigned int y1
	, unsigned int x2, unsigned int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	// We want to process the longest dimention of the line
	if (abs(dx) > abs(dy))
	{
		// Move along the x axis to draw
//		for (unsigned int i=x1;)
	}
	else
	{
		// Move along the y axis to draw
	}
}

void Graphics::drawLine(unsigned int x1, unsigned int y1
	, unsigned int x2, unsigned int y2, RGBA rgb)
{

}

void Graphics::drawLines(std::vector<std::pair<unsigned int, unsigned int>> points)
{

}
