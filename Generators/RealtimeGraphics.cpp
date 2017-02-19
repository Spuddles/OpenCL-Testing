#include "RealtimeGraphics.h"
#include "../Utils/Utils.h"
#include "../Utils/Matrix.h"

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

	return true;
}

void RealtimeGraphics::testDrawLine()
{
	RGBA	rgba{ 255,128,128,255 };

	// Drawline testing
	m_pGraphics->drawLine(100, 100, 0, 100, rgba);
	m_pGraphics->drawLine(100, 100, 0, 50, rgba);
	m_pGraphics->drawLine(100, 100, 0, 0, rgba);
	m_pGraphics->drawLine(100, 100, 50, 0, rgba);
	m_pGraphics->drawLine(100, 100, 100, 0, rgba);
	m_pGraphics->drawLine(100, 100, 150, 0, rgba);
	m_pGraphics->drawLine(100, 100, 200, 0, rgba);
	m_pGraphics->drawLine(100, 100, 200, 50, rgba);
	m_pGraphics->drawLine(100, 100, 200, 100, rgba);

	m_pGraphics->drawLine(100, 100, 200, 150, rgba);
	m_pGraphics->drawLine(100, 100, 200, 200, rgba);
	m_pGraphics->drawLine(100, 100, 150, 200, rgba);
	m_pGraphics->drawLine(100, 100, 100, 200, rgba);
	m_pGraphics->drawLine(100, 100, 50, 200, rgba);
	m_pGraphics->drawLine(100, 100, 0, 200, rgba);
	m_pGraphics->drawLine(100, 100, 0, 150, rgba);
}

void RealtimeGraphics::testSetPixel(float time)
{
	RGBA	rgba{ 255,128,128,255 };

	// setPixel testing
	for (int i=0; i < 16; i++)
	{
	int x = (int)(100 + i + (time * 10)) % 640;
	int y = (int)(100 + i + (time * 10)) % 400;

	m_pGraphics->setPixel(x, y, rgba);
	}
}

void RealtimeGraphics::testDrawPolygon()
{
	RGBA	rgba{ 255,128,128,255 };

	// Draw polygon testing
	std::vector<std::pair<unsigned int, unsigned int>>	points{ {100,100}, {200,100}, {200,200}, {100,200} };
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

		m_pGraphics->drawFatLine(a.x, a.y, b.x, b.y, a.rgb);
	}
}

void RealtimeGraphics::testSolidPolygon()
{
	RGBA	rgba{ 255,128,128,255 };

	// Draw solid polygon testing
	std::vector<std::pair<unsigned int, unsigned int>>	points{ { 100,100 },{ 300,100 },{ 300,300 },{ 100,300 } };
	m_pGraphics->drawSolidPolygon(points, rgba);
}

void RealtimeGraphics::testRotatingSolidPolygon(float time)
{
	RGBA	rgba{ 255,128,128,255 };

	std::vector<std::pair<unsigned int, unsigned int>>	points{ { 200,100 },{ 300,100 },{ 300,300 },{ 200,300 } };

	// Rotate the points
	for (auto &p : points)
	{
		float x = (int)p.first - 320;
		float y = (int)p.second - 200;
		Matrix::RotateZ(x, y, time);
		p.first = (unsigned int)x + 320;
		p.second = (unsigned int)y + 200;
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