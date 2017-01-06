#include "ConsoleColours.h"

ConsoleColours::ConsoleColours()
{
}

ConsoleColours::~ConsoleColours()
{
}

bool ConsoleColours::initialise()
{
	return true;
}

bool ConsoleColours::run(RGBA *input, RGBA *output)
{
	for (int i = 0; i < 640 * 400; i++)
	{
		RGBA rgba = (*input++);
		int offset = -1;
		float closest = 10e15;

		// Look for the closest colour in 3D space
		for (int i=0;i<vecColours.size();++i)
		{
			RGBA col = vecColours[i];

			int dr = rgba.R - col.R;
			int dg = rgba.G - col.G;
			int db = rgba.B - col.B;

			float dist = (dr*dr) + (dg*dg) + (db*db);

			if (dist < closest)
			{
				offset = i;
				closest = dist;
			}
		}

		// Write out the console RGB version
		*(output++) = vecColours[offset];
	}
	return true;
}

std::string	ConsoleColours::getName()
{
	return "Console Colours";
}
