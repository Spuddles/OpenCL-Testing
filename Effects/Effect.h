#pragma once
#include <string>
#include "../Utils/Structs.h"

class Effect
{
public:
	virtual bool	initialise()=0;
	virtual bool	run(RGBA *input, RGBA *output)=0;
	virtual std::string	getName()=0;

};
