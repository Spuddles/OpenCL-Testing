#pragma once
#include "Generator.h"

class StaticImage : public Generator
{
public:
	StaticImage(const std::string &fileName);
	~StaticImage();

	virtual bool		initialise();
	virtual bool		run(float time, RGBA *output);
	virtual std::string	getName();

private:
	std::string			m_FileName;
	RGBA				*m_ImageData;
};

