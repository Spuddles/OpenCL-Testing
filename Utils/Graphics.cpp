#include "Graphics.h"
#include <cassert>

Graphics::Graphics(unsigned int width, unsigned int height):
	m_Width(width)
	,m_Height(height)
{
	m_RightEdge.resize(m_Height);
	m_LeftEdge.resize(m_Height);
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
			std::swap(x1, x2);
			std::swap(y1, y2);
			dx = dx*-1.0f;
			dy = dy*-1.0f;
		}

		// Move along the x axis to draw
		for (unsigned int x = x1; x < x2; x++)
		{
			int y = y1 + (dy*((x - x1) / dx));
			setPixel(x, y, rgb);
		}
	}
	else
	{
		if (y1 > y2)
		{
			// Flip the co-ords so we can process top to bottom
			std::swap(x1, x2);
			std::swap(y1, y2);
			dx = dx*-1.0f;
			dy = dy*-1.0f;
		}

		// Move along the y axis to draw
		for (unsigned int y = y1; y < y2; y++)
		{
			int x = x1 + (dx*((y - y1) / dy));
			setPixel(x, y, rgb);
		}
	}
}

void Graphics::drawLineIntoEdges(int x1, int y1, int x2, int y2)
{
	if (y1 > y2)
	{
		// Flip the co-ords so we can process top to bottom
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	float dx = x2 - x1;
	float dy = y2 - y1;

	// Move along the y axis to draw
	for (unsigned int y = y1; y < y2; y++)
	{
		int x = x1 + (dx*((y - y1) / dy));

		if (m_LeftEdge[y] > x)
			m_LeftEdge[y] = x;
		if (m_RightEdge[y] < x)
			m_RightEdge[y] = x;
	}
}

void Graphics::drawFatLine(int x1, int y1
	, int x2, int y2, RGBA rgb)
{
	drawLine(x1, y1, x2, y2, rgb);

	drawLine(x1+1, y1, x2+1, y2, rgb);
	drawLine(x1, y1+1, x2, y2+1, rgb);
	drawLine(x1-1, y1, x2-1, y2, rgb);
	drawLine(x1, y1-1, x2, y2-1, rgb);
}

	void Graphics::drawLines(const std::vector<std::pair<unsigned int, unsigned int>> &points)
{
	drawLines(points, m_DefaultColour);
}

void Graphics::drawLines(const std::vector<std::pair<unsigned int, unsigned int>> &points, RGBA rgb)
{
	for (size_t i = 0; i < points.size(); i++)
	{
		auto &a = points[i];
		auto &b = points[(i + 1) % points.size()];

		drawFatLine(a.first, a.second, b.first, b.second, rgb);
	}
}

void Graphics::fillBetweenEdges(RGBA rgb)
{
	for (int y = 0; y < m_Height; y++)
	{
		if (m_LeftEdge[y] > -1 && m_RightEdge[y] > -1)
		{
			fillHorizontal(m_LeftEdge[y], m_RightEdge[y], y, rgb);
		}
	}
}

void Graphics::fillHorizontal(int x1, int x2, int y, RGBA rgb)
{
	int offset = (y*m_Width) + x1;
	for (int x = x1; x <= x2; x++)
	{
		m_Bitmap[offset++] = rgb;
	}
}

void Graphics::drawSolidPolygon(const std::vector<std::pair<unsigned int, unsigned int>> &points, RGBA rgb)
{
	// Clear the edge buffers
	for (int i = 0; i < m_LeftEdge.size(); i++)
	{
		m_LeftEdge[i] = m_Width+1;
		m_RightEdge[i] = -1;
	}

	// Render each line into the buffer
	for (int i = 0; i < points.size(); i++)
	{
		auto &a = points[i];
		auto &b = points[(i+1)%points.size()];

		drawLineIntoEdges(a.first, a.second, b.first, b.second);
	}

	// Fill in the gaps
	fillBetweenEdges(rgb);
}
