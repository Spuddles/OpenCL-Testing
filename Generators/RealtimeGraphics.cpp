#include "RealtimeGraphics.h"
#include "../Utils/Utils.h"
#include "../Utils/Matrix.h"
#include "../Utils/Point.h"

#include <cassert>

RealtimeGraphics::RealtimeGraphics()
{
}

RealtimeGraphics::~RealtimeGraphics()
{
	if (m_pGraphics)
		delete m_pGraphics;
}

bool RealtimeGraphics::initialise()
{
	m_pGraphics = new Graphics(640, 400);

	m_vecPoints.reserve(10);
	for (int i = 0; i < 100; i++)
	{
		point p;

		p.x = std::rand() % 640;
		p.y = std::rand() % 400;
		p.dx = (std::rand() % 6)-3;
		p.dy = (std::rand() % 6)-3;
		p.rgb.R = std::rand() % 255;
		p.rgb.G = std::rand() % 255;
		p.rgb.B = std::rand() % 255;
		p.rgb.A = 255;

		m_vecPoints.push_back(p);
	}

	m_Texture.loadTexture("..//Images//Yoshi-256x256.data", 256, 256);

	return true;
}

void RealtimeGraphics::testDrawLine()
{
	RGBA	rgba{ 255,128,128,255 };

	// Drawline testing
	Point<int>	p(100, 100);
	m_pGraphics->drawLine(p, Point<int>(0, 100), rgba);
	m_pGraphics->drawLine(p, Point<int>(0, 50), rgba);
	m_pGraphics->drawLine(p, Point<int>(0, 0), rgba);
	m_pGraphics->drawLine(p, Point<int>(50, 0), rgba);
	m_pGraphics->drawLine(p, Point<int>(100, 0), rgba);
	m_pGraphics->drawLine(p, Point<int>(150, 0), rgba);
	m_pGraphics->drawLine(p, Point<int>(200, 0), rgba);
	m_pGraphics->drawLine(p, Point<int>(200, 50), rgba);
	m_pGraphics->drawLine(p, Point<int>(200, 100), rgba);

	m_pGraphics->drawLine(p, Point<int>(200, 150), rgba);
	m_pGraphics->drawLine(p, Point<int>(200, 200), rgba);
	m_pGraphics->drawLine(p, Point<int>(150, 200), rgba);
	m_pGraphics->drawLine(p, Point<int>(100, 200), rgba);
	m_pGraphics->drawLine(p, Point<int>(50, 200), rgba);
	m_pGraphics->drawLine(p, Point<int>(0, 200), rgba);
	m_pGraphics->drawLine(p, Point<int>(0, 150), rgba);
}

void RealtimeGraphics::testSetPixel(float time)
{
	RGBA	rgba{ 255,128,128,255 };

	// setPixel testing
	Point<int>	p;
	for (int i=0; i < 16; i++)
	{
	p.x = (int)(100 + i + (time * 10)) % 640;
	p.y = (int)(100 + i + (time * 10)) % 400;

	m_pGraphics->setPixel(p, rgba);
	}
}

void RealtimeGraphics::testDrawPolygon()
{
	RGBA	rgba{ 255,128,128,255 };

	// Draw polygon testing
	std::vector<Point<int>>	points{ Point<int>(100,100), Point<int>(200,100), Point<int>(200,200), Point<int>(100,200) };
	m_pGraphics->drawLines(points, rgba);
}

void RealtimeGraphics::testDrawFatLines()
{
	for (int i = 0; i < m_vecPoints.size(); i++)
	{
		// Update position
		point &p = m_vecPoints[i];

		p.x += p.dx;
		p.y += p.dy;

		if (p.x > 638)
		{
		p.x = 638;
		p.dx = (std::rand() % 3) - 3;
		}
		else if (p.x < 1)
		{
		p.x = 1;
		p.dx = (std::rand() % 3) + 1;
		}

		if (p.y > 398)
		{
		p.y = 398;
		p.dy = (std::rand() % 3) - 3;
		}
		else if (p.y < 1)
		{
		p.y = 1;
		p.dy = (std::rand() % 3) + 1;
		}
		}

		for (int i = 0; i < m_vecPoints.size() - 1; i++)
		{
		point &a = m_vecPoints[i];
		point &b = m_vecPoints[i + 1];

		m_pGraphics->drawFatLine(Point<int>(a.x, a.y), Point<int>(b.x, b.y), a.rgb);
	}
}

void RealtimeGraphics::testSolidPolygon()
{
	RGBA	rgba{ 255,128,128,255 };

	// Draw solid polygon testing
	std::vector<Point<int>>	points{ Point<int>(100,100),Point<int>(300,100), Point<int>(300,300), Point<int>(100,300) };
	m_pGraphics->drawSolidPolygon(points, rgba);
}

void RealtimeGraphics::testRotatingSolidPolygon(float time)
{
	RGBA	rgba{ 255,128,128,255 };

//	std::vector<std::pair<unsigned int, unsigned int>>	points{ { 200,100 },{ 300,100 },{ 300,300 },{ 200,300 } };
	std::vector<Point<int>>	points{ Point<int>(-50,-100),Point<int>(+50,-100),Point<int>(+50,100),Point<int>(-50,100) };
//	std::vector<std::pair<float, float>>	tex{ { 0,0 }, { 1,0 }, { 1,1 }, { 0,1 } };

	// Rotate the points
	for (auto &p : points)
	{
		float x = p.x;
		float y = p.y;
		Matrix::RotateZ(x, y, time);
		p.x = (int)x + 200;
		p.y = (int)y + 200;
	}

	// Draw solid polygon testing
	m_pGraphics->drawSolidPolygon(points, rgba);
}

bool RealtimeGraphics::run(float time, RGBA *output)
{
	m_pGraphics->setBitmap(output);
	m_pGraphics->clear();

	//testDrawline();
	//testSetPixel(time);
	//testDrawPolygon();
	//testDrawFatLines();
	//testSolidPolygon();
	testRotatingSolidPolygon(time);

	return true;
}

std::string	RealtimeGraphics::getName()
{
	return "Realtime Graphics";
}