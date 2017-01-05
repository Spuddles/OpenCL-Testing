#pragma once
#include <vector>

struct RGBA
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
};

static std::vector<RGBA> vecColours{
	{ 0,0,0 },
	{ 0,0,128 },
	{ 0,128,0 },
	{ 0,128,128 },
	{ 128,0,0 },
	{ 128,0,128 },
	{ 128,128,0 },
	{ 192,192,192 },
	{ 128,128,128 },
	{ 0,0,255 },
	{ 0,255,0 },
	{ 0,255,255 },
	{ 255,0,0 },
	{ 255,0,255 },
	{ 255,255,0 },
	{ 255,255,255 } };
