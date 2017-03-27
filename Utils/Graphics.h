#pragma once
#include "Structs.h"
#include "Point.h"

#include <vector>
class Graphics
{
public:
	Graphics(unsigned int width, unsigned int height);
	~Graphics();

	void	setBitmap(RGBA *bitmap);
	void	setColour(RGBA rgb);

	void	clear();

	void	setPixel(Point<int> p);
	void	setPixel(Point<int> p, RGBA rgb);

	void	drawLine(Point<int> p1, Point<int> p2);
	void	drawLine(Point<int> p1, Point<int> p2, RGBA rgb);
	void	drawFatLine(Point<int> p1, Point<int> p2, RGBA rgb);

	void	drawLines(const std::vector<Point<int>> &points);
	void	drawLines(const std::vector<Point<int>> &points, RGBA rgb);

	void	drawSolidPolygon(const std::vector<Point<int>> &points, RGBA rgb);

private:
	void	drawLineIntoEdges(Point<int> p1, Point<int> p2);
	void	fillBetweenEdges(RGBA rgb);
	void	fillHorizontal(int x1, int x2, int y, RGBA rgb);


	unsigned int	m_Width;
	unsigned int	m_Height;

	RGBA			*m_Bitmap{ nullptr };
	RGBA			m_DefaultColour;

	std::vector<std::pair<int, float>>	m_LeftEdge;
	std::vector<std::pair<int, float>>	m_RightEdge;
};

