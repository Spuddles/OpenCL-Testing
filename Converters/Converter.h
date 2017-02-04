#pragma once
#include <Windows.h>
#include <string>
#include "../Utils/Structs.h"

class Converter
{
public:
	virtual bool	initialise()=0;
	virtual bool	convert(RGBA *input, CHAR_INFO *output)=0;
	virtual bool	convertBack(CHAR_INFO *input, RGBA *output) = 0;
	virtual std::string	getName()=0;

};
