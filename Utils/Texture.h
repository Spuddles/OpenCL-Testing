#pragma once
#include <string>
#include "Structs.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool			loadTexture(const std::string &fileName, unsigned int width, unsigned int height);
	unsigned int	getWidth() const;
	unsigned int	getHeight() const;
	RGBA			getTexel(float u, float v) const;

private:
	unsigned int	m_Width{ 0 };
	unsigned int	m_Height{ 0 };
	RGBA			*m_pTexture{ nullptr };
};

