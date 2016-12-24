#pragma once
#undef UNICODE
#include <Windows.h>

#include <vector>

class CharSelection
{
public:
	CharSelection();
	~CharSelection();

	void	Init();
	void	Run(CHAR_INFO* screen, int offset);

private:
	void	DumpChar(unsigned char* image);
	float	Test(unsigned char* source, unsigned char* block);
	void	ExtractChar(unsigned char* output, int letter);
	void	ExtractFromImage(unsigned char* output, int x, int y);

	unsigned char*	m_CharSet = nullptr;
	unsigned char*	m_Image = nullptr;

	//std::vector<int>	m_ValidChars = { 32,48,49,50,51,52,53,54,55,56,57 }; // Numbers
	std::vector<int>	m_ValidChars = { 32,7,8,9,10,43,46,48,79,111,233,254 }; // Dots
	//std::vector<int>	m_ValidChars = { 32,176,177,178 }; // Grids

	int m_Offset = 0;
};

