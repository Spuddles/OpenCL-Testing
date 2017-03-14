#pragma once
#include "Structs.h"
#include <vector>
class Graphics
{
public:
	Graphics(unsigned int width, unsigned int height);
	~Graphics();

	void	setBitmap(RGBA *bitmap);
	void	setColour(RGBA rgb);

	void	clear();

	void	setPixel(unsigned int x, unsigned int y);
	void	setPixel(unsigned int x, unsigned int y, RGBA rgb);

	void	drawLine(int x1, int y1
					,int x2, int y2);
	void	drawLine(int x1, int y1
					,int x2, int y2, RGBA rgb);
	void	drawFatLine(int x1, int y1
					  , int x2, int y2, RGBA rgb);

	void	drawLines(const std::vector<std::pair<unsigned int, unsigned int>> &points);
	void	drawLines(const std::vector<std::pair<unsigned int, unsigned int>> &points, RGBA rgb);

	void	drawSolidPolygon(const std::vector<std::pair<unsigned int, unsigned int>> &points, RGBA rgb);

private:
	void	drawLineIntoEdges(int x1, int y1, int x2, int y2);
	void	fillBetweenEdges(RGBA rgb);
	void	fillHorizontal(int x1, int x2, int y, RGBA rgb);


	unsigned int	m_Width;
	unsigned int	m_Height;

	RGBA			*m_Bitmap{ nullptr };
	RGBA			m_DefaultColour{ 0 };

	std::vector<std::pair<int, float>>	m_LeftEdge;
	std::vector<std::pair<int, float>>	m_RightEdge;

};

