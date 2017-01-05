#pragma once
#include <string>

class Utils
{
public:
	Utils();
	~Utils();

	static std::string loadFile(const std::string &filename);
	static char* loadBinaryFile(const std::string &filename);
	static bool  loadBinaryFile(const std::string &filename, char* buffer);
};

