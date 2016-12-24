#include "CharSelection.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

CharSelection::CharSelection()
{
}


CharSelection::~CharSelection()
{
}

void CharSelection::Init()
{
	// Load the bitmap font file
	m_CharSet = (unsigned char*)Utils::loadBinaryFile("Charset.data");

	// Load the test image
//	m_Image = (unsigned char*) Utils::loadBinaryFile("Images//BW-Dragon.data");
//	m_Image = (unsigned char*) Utils::loadBinaryFile("Images//BW-Swirls.data");
	m_Image = (unsigned char*) Utils::loadBinaryFile("Images//BW-RevisionLogo.data");
}

void CharSelection::DumpChar(unsigned char* image)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (*(image++) > 0)
				std::cout << (char) 219;
			else
				std::cout << ".";
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
			*(output++) = *(buffer++);
		}
		buffer += 120;
	}
}

void CharSelection::ExtractFromImage(unsigned char* output, int x, int y)
{
	unsigned char* buffer = m_Image + (x * 8*4) + (y * 8*4*640);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int rgb = *(buffer++) + *(buffer++) + *(buffer++);
			if (rgb > (128*2))
				*(output++) = 1;
			else
				*(output++) = 0;

			buffer++;
		}
		buffer += (640-8)*4;
	}
}

float CharSelection::Test(unsigned char* source, unsigned char* block)
{
	// Simple matching test
	float score = 0.0f;
	for (int i = 0; i < 64; i++)
	{
		if (*(source++) == *(block++))
			score += 1.0f;
		else
			score -= 1.0f;
	}
	return score/64.0f;
}

void CharSelection::Run()
{
	std::vector<std::pair<int, float>>	vecScores;

	unsigned char imageBlock[64]={0};
	unsigned char fontBlock[64] = { 0 };

	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			// Get the image block for the current co-ords
			ExtractFromImage(imageBlock, x, y);

			// Go through all the font blocks looking for the closes
			vecScores.clear();

			for (int i = 32; i < 256; i++)
			{
				ExtractChar(fontBlock, i);

				float score = Test(imageBlock, fontBlock);
				vecScores.push_back(std::make_pair(i, score));
			}

			std::sort(vecScores.begin(), vecScores.end(),
				[](const std::pair<int, float>& a, const std::pair<int, float> & b) -> bool
			{
//				return abs(a.second) > abs(b.second);
				return a.second > b.second;
			});

			// Print out the most accurate char
			std::cout << (char) vecScores[0].first;
		}
		std::cout << std::endl;
	}
}
