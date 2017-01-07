#include "Utils.h"
#include <fstream>
#include <sstream>
#include <cassert>

Utils::Utils()
{
}

Utils::~Utils()
{
}

std::string Utils::loadFile(const std::string &filename)
{
	std::ifstream input(filename);
	if (input)
	{
		std::ostringstream contents;

		contents << input.rdbuf();

		return contents.str();
	}
	return "";
}

char* Utils::loadBinaryFile(const std::string &filename)
{
	std::ifstream input(filename, std::ios_base::binary | std::ios_base::ate);
	if (!input.bad() && !input.fail())
	{
		size_t filesize = input.tellg();
		input.seekg(0);

		char *data = new char[filesize];

		input.read( data, filesize);

		return data;
	}
	return nullptr;
}

bool Utils::loadBinaryFile(const std::string &filename, char* buffer)
{
	std::ifstream input(filename, std::ios_base::binary | std::ios_base::ate);
	if (!input.bad() && !input.fail())
	{
		size_t filesize = input.tellg();
		input.seekg(0);

		input.read(buffer, filesize);

		input.close();

		return true;
	}
	return false;
}

bool Utils::saveBinaryFile(const std::string &filename, char* buffer, int amount)
{
	std::ofstream output(filename, std::ios_base::binary);
	if (output)
	{
		output.write(buffer, amount);
		output.close();
		return true;
	}
	return false;
}

/*
 * This function assumes we are playing with images with pixels stored as RGBA
 * which means 4 bytes per pixel
 */
bool Utils::extractFromImage(char *input, int inputwidth, int inputheight,
							char *output, int outputwidth, int outputheight, int x, int y )
{
	assert(inputwidth*inputheight >= ((outputheight*inputwidth*(y + 1))*(outputwidth*(x + 1))));
	const int bytesperpixel = 4;
	char* buffer = input + (x * outputwidth * bytesperpixel) + (y * outputheight * bytesperpixel * inputwidth);

	for (int i = 0; i < outputheight; i++)
	{
		for (int j = 0; j < outputwidth; j++)
		{
			for (int b = 0; b < bytesperpixel; b++)
			{
				*(output++) = *(buffer++);
			}
		}
		buffer += (inputwidth - outputwidth) * bytesperpixel;
	}
	return true;
}