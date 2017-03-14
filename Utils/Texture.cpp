#include "Texture.h"
#include "Utils.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::loadTexture(const std::string &fileName, unsigned int width, unsigned int height)
{
	m_Width = width;
	m_Height = height;

	m_pTexture = new RGBA[width*height];

	return Utils::loadBinaryFile(fileName, (char*)m_pTexture);
}

unsigned int Texture::getWidth() const
{
	return m_Width;
}

unsigned int Texture::getHeight() const
{
	return m_Height;
}

RGBA Texture::getTexel(float u, float v) const
{
	unsigned int x = (unsigned int)(u * m_Width);
	unsigned int y = (unsigned int)(v * m_Height);

	RGBA rgba = m_pTexture[x + (y*m_Width)];

	return rgba;
}