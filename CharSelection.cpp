#include "CharSelection.h"
#include "Utils.h"
#include <iostream>

CharSelection::CharSelection()
{
}


CharSelection::~CharSelection()
{
}

void CharSelection::Init()
{
	// Load the bitmap font file
	m_CharSet = (unsigned char*)Utils::loadBinaryFile("CharSet.data");

}

void CharSelection::DumpChar(unsigned char* image)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (*image > 0)
				std::cout << "*";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void CharSelection::ExtractChar(unsigned char* output, int letter)
{
	int x = letter % 16;
	int y = letter / 16;

	unsigned char* buffer = m_CharSet + (x * 8) + (y * 1024);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			*output++ = *buffer++;
		}
		buffer += 120;
	}
}

float CharSelection::Test(unsigned char* source, unsigned char* block)
{
	// Simple matching test
	float score = 0.0f;
	for (int i = 0; i < 64; i++)
	{
		if (*source++ == *block++)
			score += 1.0f;
		else
			score -= 1.0f;
	}
	return score/64.0f;
}

void CharSelection::Run()
{
	unsigned char source[64]={0,0,0,0,0,0,0,0
							 ,0,0,0,0,0,0,0,0
							 ,0,0,0,0,0,0,0,0
							 ,0,0,0,0,0,0,0,0
							 ,0,0,0,0,0,0,0,0
							 ,0,0,0,0,0,0,0,0
							 ,0,0,0,0,0,0,0,0
							 ,0,0,0,0,0,0,0,0};

	unsigned char tile[64] = { 0 };

	std::cout << "Test block is:" << std::endl;
	DumpChar(source);

	// Run through each char and generate a score against source image

	for (int i = 0; i < 256; i++)
	{
		ExtractChar(tile, i);

		std::cout << "Test char " << i << " is:" << std::endl;
		DumpChar(tile);

		float score = Test(source, tile);

		std::cout << "Character " << i << " has a score of " << score << std::endl;
	}
}
