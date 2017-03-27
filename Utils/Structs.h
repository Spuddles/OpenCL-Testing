#pragma once
#include <vector>

struct RGBA
{
	unsigned char R{ 0 };
	unsigned char G{ 0 };
	unsigned char B{ 0 };
	unsigned char A{ 0 };

	RGBA() {};
	RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :R(r), G(g), B(b), A(a) {}
};

static std::vector<RGBA> vecColours{
	{ 0,0,0,255 },
	{ 0,0,128,255 },
	{ 0,128,0,255 },
	{ 0,128,128,255 },
	{ 128,0,0,255 },
	{ 128,0,128,255 },
	{ 128,128,0,255 },
	{ 192,192,192,255 },
	{ 128,128,128,255 },
	{ 0,0,255,255 },
	{ 0,255,0,255 },
	{ 0,255,255,255 },
	{ 255,0,0,255 },
	{ 255,0,255,255 },
	{ 255,255,0,255 },
	{ 255,255,255,255 } };
