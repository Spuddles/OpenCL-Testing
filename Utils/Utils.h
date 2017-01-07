#pragma once
#include <string>

class Utils
{
public:
	static std::string loadFile(const std::string &filename);
	static char* loadBinaryFile(const std::string &filename);
	static bool  loadBinaryFile(const std::string &filename, char* buffer);
	static bool  saveBinaryFile(const std::string &filename, char* buffer, int length);

	static bool  extractFromImage(char *input, int inputwidth, int inputheight,
		char *output, int outputwidth, int outputheight, int x, int y);

private:
	Utils();
	~Utils();
};

