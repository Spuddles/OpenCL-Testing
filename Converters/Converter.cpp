#include "Converter.h"
#include "../Utils/Utils.h"

bool Converter::initialise()
{
	// Load in the charset
	m_CharSet = Utils::loadBinaryFile("..//Images//Charset-ordered.data");
	if (!m_CharSet)
		return false;

	return true;
}

unsigned char Converter::getConsoleColour(RGBA rgb)
{
	int offset = -1;
	float closest = 10e15;

	// Look for the closest colour in 3D space
	for (int i = 0; i<vecColours.size(); ++i)
	{
		RGBA col = vecColours[i];

		int dr = rgb.R - col.R;
		int dg = rgb.G - col.G;
		int db = rgb.B - col.B;

		float dist = (dr*dr) + (dg*dg) + (db*db);

		if (dist < closest)
		{
			offset = i;
			closest = dist;
		}
	}
	return static_cast<unsigned char>(offset);
}


bool Converter::convertBack(CHAR_INFO *input, RGBA *output)
{
	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			int offset = (y * 80) + x;

			unsigned char c = input[offset].Char.AsciiChar;
			unsigned char fg = input[offset].Attributes % 16;
			unsigned char bg = input[offset].Attributes / 16;
			char* fontdata = m_CharSet + (c * 64);

			for (int v = 0; v < 8; v++)
			{
				for (int u = 0; u < 8; u++)
				{
					RGBA *write = output + (y * 640 * 8) + (x * 8) + (v * 640) + u;
					if (*fontdata > 0)
					{
						*write = vecColours[fg];
						write->A = 255;
					}
					else
					{
						*write = vecColours[bg];
						write->A = 255;
					}
					fontdata++;
				}
			}
		}
	}
	return true;
}
