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
	for (unsigned int i = 0; i < (m_Width*m_Height); i++)
	{
		m_Bitmap[i] = rgba;
	}
}

void Graphics::setPixel(Point<int> p)
{
	unsigned int offset = (p.y*m_Width) + p.x;
	assert(offset < m_Width*m_Height);

	m_Bitmap[offset] = m_DefaultColour;
}

void Graphics::setPixel(Point<int> p, RGBA rgb)
{
	unsigned int offset = (p.y*m_Width) + p.x;
	assert(offset < m_Width*m_Height);

	m_Bitmap[offset] = rgb;
}

void Graphics::drawLine(Point<int> p1, Point<int> p2)
{
	drawLine(p1, p2, m_DefaultColour);
}

void Graphics::drawLine(Point<int> p1, Point<int> p2, RGBA rgb)
{
	float dx = static_cast<float>(p2.x - p1.x);
	float dy = static_cast<float>(p2.y - p1.y);

	// We want to process the longest dimention of the line
	if (abs(dx) > abs(dy))
	{
		if (p1.x > p2.x)
		{
			// Flip the co-ords so we can process left to right
			std::swap(p1.x, p2.x);
			std::swap(p1.y, p2.y);
			dx = dx*-1.0f;
			dy = dy*-1.0f;
		}

		// Move along the x axis to draw
		for (int x = p1.x; x < p2.x; x++)
		{
			int y = static_cast<int>(p1.y + (dy*((x - p1.x) / dx)));
			setPixel(Point<int>(x, y), rgb);
		}
	}
	else
	{
		if (p1.y > p2.y)
		{
			// Flip the co-ords so we can process top to bottom
			std::swap(p1.x, p2.x);
			std::swap(p1.y, p2.y);
			dx = dx*-1.0f;
			dy = dy*-1.0f;
		}

		// Move along the y axis to draw
		for (int y = p1.y; y < p2.y; y++)
		{
			int x = static_cast<int>(p1.x + (dx*((y - p1.y) / dy)));
			setPixel(Point<int>(x, y), rgb);
		}
	}
}

void Graphics::drawLineIntoEdges(Point<int> p1, Point<int> p2)
{
	if (p1.y > p2.y)
	{
		// Flip the co-ords so we can process top to bottom
		std::swap(p1, p2);
	}

	float dx = static_cast<float>(p2.x - p1.x);
	float dy = static_cast<float>(p2.y - p1.y);

	// Move along the y axis to draw
	for (int y = p1.y; y < p2.y; y++)
	{
		int x = static_cast<int>(p1.x + (dx*((y - p1.y) / dy)));

		if (m_LeftEdge[y].first > x)
			m_LeftEdge[y].first = x;
		if (m_RightEdge[y].first < x)
			m_RightEdge[y].first = x;
	}
}

void Graphics::drawFatLine(Point<int> p1, Point<int> p2, RGBA rgb)
{
	drawLine(p1, p2, rgb);

	p1.x++; p2.x++;
	drawLine(p1, p2, rgb);

	p1.x--; p2.x--; p1.y++; p2.y++;
	drawLine(p1, p2, rgb);

	p1.y--; p2.y--; p1.x--; p2.x--;
	drawLine(p1, p2, rgb);

	p1.x++; p2.x++; p1.y--; p2.y--;
	drawLine(p1, p2, rgb);
}

void Graphics::drawLines(const std::vector<Point<int>> &points)
{
	drawLines(points, m_DefaultColour);
}

void Graphics::drawLines(const std::vector<Point<int>> &points, RGBA rgb)
{
	for (size_t i = 0; i < points.size(); i++)
	{
		Point<int> p1 = points[i];
		Point<int> p2 = points[(i + 1) % points.size()];

		drawFatLine(p1, p2, rgb);
	}
}

void Graphics::fillBetweenEdges(RGBA rgb)
{
	for (unsigned int y = 0; y < m_Height; y++)
	{
		if (m_LeftEdge[y].first > -1 && m_RightEdge[y].first > -1)
		{
			fillHorizontal(m_LeftEdge[y].first, m_RightEdge[y].first, y, rgb);
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

void Graphics::drawSolidPolygon(const std::vector<Point<int>> &points, RGBA rgb)
{
	// Clear the edge buffers
	for (int i = 0; i < m_LeftEdge.size(); i++)
	{
		m_LeftEdge[i].first = m_Width+1;
		m_RightEdge[i].first = -1;
	}

	// Render each line into the buffer
	for (int i = 0; i < points.size(); i++)
	{
		auto &p1 = points[i];
		auto &p2 = points[(i+1)%points.size()];

		drawLineIntoEdges(p1, p2);
	}

	// Fill in the gaps
	fillBetweenEdges(rgb);
}
