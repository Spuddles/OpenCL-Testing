#pragma once
#include "Generator.h"
#include "../Utils/Graphics.h"

class RealtimeGraphics : public Generator
{
public:
	RealtimeGraphics();
	~RealtimeGraphics();

	virtual bool		initialise();
	virtual bool		run(float time, RGBA *output);
	virtual std::string	getName();

private:
	Graphics			*m_pGraphics{ nullptr };
};

