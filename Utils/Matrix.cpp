#include "Matrix.h"
#include <cassert>

Matrix4f::Matrix4f()
{
}

Matrix4f::Matrix4f(float value)
{
	for (int i = 0; i < 16; i++)
	{
		m_Data[i] = value;
	}
}

Matrix4f::Matrix4f(float values[16])
{
	for (int i = 0; i < 16; i++)
	{
		m_Data[i] = values[i];
	}
}

Matrix4f::~Matrix4f()
{
}

bool Matrix4f::operator==(const Matrix4f &m)
{
	for (int i = 0; i < 16; i++)
	{
		if (m_Data[i] != m.get(i % 4, i / 4))
			return false;
	}
	return true;
}

float Matrix4f::get(unsigned int x, unsigned int y) const
{
	assert(x <= 3);
	assert(y <= 3);

	return m_Data[x + (y * 4)];
}

void Matrix4f::rotateX(float d)
{
	m_Data[5] = std::cos(d);
	m_Data[6] = -std::sin(d);

	m_Data[9] = std::sin(d);
	m_Data[10] = std::cos(d);
}

void Matrix4f::rotateY(float d)
{
	m_Data[0] = std::cos(d);
	m_Data[2] = std::sin(d);

	m_Data[8] = -std::sin(d);
	m_Data[10] = std::cos(d);
}

void Matrix4f::rotateZ(float d)
{
	m_Data[0] = std::cos(d);
	m_Data[4] = -std::sin(d);

	m_Data[1] = std::sin(d);
	m_Data[5] = std::cos(d);
}

void Matrix4f::transform(float X, float Y, float Z)
{
	m_Data[12] = X;
	m_Data[13] = Y;
	m_Data[14] = Z;
}

void Matrix4f::transformX(float X)
{
	m_Data[12] = X;
}

void Matrix4f::transformY(float Y)
{
	m_Data[13] = Y;
}

void Matrix4f::transformZ(float Z)
{
	m_Data[14] = Z;
}

void Matrix4f::setIdentity()
{
	for (int i = 0; i < 16; i++)
	{
		m_Data[i] = 0.0f;
	}
	m_Data[0] = 1.0f;
	m_Data[5] = 1.0f;
	m_Data[10] = 1.0f;
	m_Data[15] = 1.0f;
}
