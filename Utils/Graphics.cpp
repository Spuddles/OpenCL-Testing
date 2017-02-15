#include "Graphics.h"

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

}

void Graphics::setColour(RGBA rgb)
{

}

void Graphics::setPixel(unsigned int x, unsigned int y)
{

}

void Graphics::setPixel(unsigned int x, unsigned int y, RGBA rgb)
{

}

void Graphics::drawLine(unsigned int x1, unsigned int y1
	, unsigned int x2, unsigned int y2)
{

}

void Graphics::drawLine(unsigned int x1, unsigned int y1
	, unsigned int x2, unsigned int y2, RGBA rgb)
{

}

void Graphics::drawLines(std::vector<std::pair<unsigned int, unsigned int>> points)
{

}
