#include "RealtimeGraphics.h"
#include "../Utils/Utils.h"

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
	m_LeftEdge.resize(400);
	m_RightEdge.resize(400);
	assert(m_LeftEdge.size() == 400);
	return true;
}

bool RealtimeGraphics::run(float time, RGBA *output)
{
	m_pGraphics->setBitmap(output);
	m_pGraphics->clear();

	RGBA	rgba{ 255,128,128,255 };

	for (int i=0; i < 16; i++)
	{
		int x = (int)(100 + i + (time * 10)) % 640;
		int y = (int)(100 + i + (time * 10)) % 400;

		m_pGraphics->setPixel(x, y, rgba);
	}
	return true;
}

std::string	RealtimeGraphics::getName()
{
	return "Realtime Graphics";
}