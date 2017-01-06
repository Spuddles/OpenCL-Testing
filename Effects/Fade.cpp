#include "Fade.h"
#include <algorithm>
#include <sstream>

Fade::Fade(int offset):
	m_Offset(offset)
{
}

Fade::~Fade()
{
}

bool Fade::initialise()
{
	return true;
}

bool Fade::run(RGBA *input, RGBA *output)
{
	for (int i = 0; i < 640 * 400; i++)
	{
		RGBA rgba = (*input++);
		rgba.A = 255;
		rgba.R = std::max(std::min(255, rgba.R + m_Offset), 0);
		rgba.G = std::max(std::min(255, rgba.G + m_Offset), 0);
		rgba.B = std::max(std::min(255, rgba.B + m_Offset), 0);
		*(output++) = rgba;
	}
	return true;
}

std::string	Fade::getName()
{
	std::stringstream ss;
	ss << "Fade(" << m_Offset << ")";
	return ss.str();
}
