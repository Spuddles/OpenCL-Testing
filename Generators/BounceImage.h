#pragma once
#include "Generator.h"

class BounceImage : public Generator
{
public:
	BounceImage();
	~BounceImage();

	virtual bool		initialise();
	virtual bool		run(float time, RGBA *output);
	virtual std::string	getName();

private:
	RGBA	*m_ImageData;
};

