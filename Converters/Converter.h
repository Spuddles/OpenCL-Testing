#pragma once
#include <Windows.h>
#include <string>
#include "../Utils/Structs.h"

class Converter
{
public:
	virtual bool	initialise();
	virtual bool	convert(RGBA *input, CHAR_INFO *output)=0;
	virtual std::string	getName()=0;

	bool			convertBack(CHAR_INFO *input, RGBA *output);
	unsigned char	getConsoleColour(RGBA rgb);

protected:
	char			*m_CharSet;
};
