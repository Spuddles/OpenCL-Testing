#pragma once
#include "Structs.h"

class Effect
{
	virtual bool	initialise()=0;
	virtual bool	run(RGBA *input, RGBA *output)=0;

};
