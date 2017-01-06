#pragma once
#include <string>
#include "../Utils/Structs.h"

class Converter
{
public:
	virtual bool	initialise()=0;
	virtual bool	convert(RGBA *input, unsigned char *output)=0;
	virtual std::string	getName()=0;

};
