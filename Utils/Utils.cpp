#include "Utils.h"
#include <fstream>
#include <sstream>

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
	if (!input.bad())
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
	if (input)
	{
		size_t filesize = input.tellg();
		input.seekg(0);

		input.read(buffer, filesize);

		input.close();

		return true;
	}
	return false;
}