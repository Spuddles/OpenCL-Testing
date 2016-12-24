#pragma once

class CharSelection
{
public:
	CharSelection();
	~CharSelection();

	void	Init();
	void	Run();

private:
	void	DumpChar(unsigned char* image);
	float	Test(unsigned char* source, unsigned char* block);
	void	ExtractChar(unsigned char* output, int letter);
	void	ExtractFromImage(unsigned char* output, int x, int y);

	unsigned char*	m_CharSet = nullptr;
	unsigned char*	m_Image = nullptr;
};

