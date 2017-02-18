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

	void	drawLines(std::vector<std::pair<unsigned int, unsigned int>> points);

private:
	unsigned int	m_Width;
	unsigned int	m_Height;

	RGBA			*m_Bitmap{ nullptr };
	RGBA			m_DefaultColour{ 0 };
};

