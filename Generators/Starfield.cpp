#include "Starfield.h"

Starfield::Starfield()
{
}

Starfield::~Starfield()
{
}

bool Starfield::initialise()
{
	// Generate a set of stars with location and speed
	m_vecStars.reserve(100);
	for (int i = 0; i < 100; i++)
	{
		Star	s;
		s.x = rand() % 640;
		s.y = rand() % 390;
		s.speed = 2 + rand() % 20;

		m_vecStars.push_back(s);
	}
	return true;
}

bool Starfield::run(float time, RGBA *output)
{
	RGBA	white(255, 255, 255, 255);
	RGBA	black(0,0,0, 255);

	// Clear the buffer
	for (int i = 0; i < 640 * 400; i++)
	{
		output[i] = black;
	}

	for (Star s : m_vecStars)
	{
		int y = s.y;
		int x = (s.x + (int)(time*640 / s.speed)) % 640;

		output[(640 * y) + x] = white;
		output[(640 * y) + x+1] = white;
		output[(640 * (y + 1)) + x] = white;
		output[(640 * (y + 1)) + x + 1] = white;
		output[(640 * (y + 2)) + x] = white;
		output[(640 * (y + 2)) + x + 1] = white;
		output[(640 * (y + 3)) + x] = white;
		output[(640 * (y + 3)) + x + 1] = white;
		output[(640 * (y + 4)) + x] = white;
		output[(640 * (y + 4)) + x + 1] = white;
	}
	return true;
}

std::string	Starfield::getName()
{
	return "Starfield";
}