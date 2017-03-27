#pragma once
#include "Generator.h"
#include <vector> 2

class Starfield : public Generator
{
	struct Star
	{
		int x;
		int y;
		int speed;
	};

public:
	Starfield();
	~Starfield();

	virtual bool		initialise();
	virtual bool		run(float time, RGBA *output);
	virtual std::string	getName();

private:
	std::vector<Star>	m_vecStars;
};

