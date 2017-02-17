#include "RealtimeGraphics.h"
#include "../Utils/Utils.h"

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
	return true;
}

bool RealtimeGraphics::run(float time, RGBA *output)
{
	m_pGraphics->setBitmap(output);

	RGBA	rgba{ 255,128,128,255 };

	for (int i=0; i < 16; i++)
	{
		m_pGraphics->setPixel(100 + i + (time * 10), 100 + i + (time * 10), rgba);
	}
	return true;
}

std::string	RealtimeGraphics::getName()
{
	return "Realtime Graphics";
}