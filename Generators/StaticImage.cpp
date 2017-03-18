#include "StaticImage.h"
#include "Utils.h"

StaticImage::StaticImage(const std::string &fileName):
	m_FileName(fileName)
   ,m_ImageData(nullptr)
{
}

StaticImage::~StaticImage()
{
}

bool StaticImage::initialise()
{
	m_ImageData = (RGBA*)Utils::loadBinaryFile(m_FileName);
	return m_ImageData != nullptr;
}

bool StaticImage::run(float time, RGBA *output)
{
	if (!m_ImageData)
		return false;

	// Copy the pre loaded image into the result buffer
	memcpy(output, m_ImageData, sizeof(RGBA) * 640 * 400);

	return true;
}

std::string	StaticImage::getName()
{
	return "Static Image - " + m_FileName;
}