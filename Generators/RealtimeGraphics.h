#pragma once
#include "Generator.h"
#include "../Utils/Graphics.h"

#include <vector>

class RealtimeGraphics : public Generator
{
	struct point
	{
		int	x;
		int	y;
		int dx;
		int dy;
		RGBA rgb;
	};

public:
	RealtimeGraphics();
	~RealtimeGraphics();

	virtual bool		initialise();
	virtual bool		run(float time, RGBA *output);
	virtual std::string	getName();

private:
	void				testDrawLine();
	void				testSetPixel(float time);
	void				testDrawPolygon();
	void				testDrawFatLines();
	void				testSolidPolygon();
	void				testRotatingSolidPolygon(float time);

	Graphics			*m_pGraphics{ nullptr };
	std::vector<point>	m_vecPoints;

};

