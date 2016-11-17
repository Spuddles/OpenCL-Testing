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