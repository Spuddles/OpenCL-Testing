#pragma once
#include <string>

class Utils
{
public:
	Utils();
	~Utils();

	static std::string loadFile(const std::string &filename);
};

