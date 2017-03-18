#pragma once
#include <string>
#include "Structs.h"

class Generator
{
public:
	virtual bool		initialise()=0;
	virtual bool		run(float time, RGBA *output)=0;
	virtual std::string	getName()=0;
};
