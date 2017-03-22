#include "Matrix.h"
#include <cassert>
#include <iostream>
#include <iomanip>

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

bool Matrix4f::operator!=(const Matrix4f &m)
{
	for (int i = 0; i < 16; i++)
	{
		if (m_Data[i] != m.get(i % 4, i / 4))
			return true;
	}
	return false;
}

Matrix4f Matrix4f::operator+(const Matrix4f &m)
{
	Matrix4f result(234.0f);

	for (int i = 0; i < 16; i++)
	{
		float value = m_Data[i] + m.get(i % 4, i / 4);
		result.set(i % 4, i / 4, value);
	}
	return result;
}

Matrix4f Matrix4f::operator-(const Matrix4f &m)
{
	Matrix4f result(234.0f);

	for (int i = 0; i < 16; i++)
	{
		float value = m_Data[i] - m.get(i % 4, i / 4);
		result.set(i % 4, i / 4, value);
	}
	return result;
}

Matrix4f Matrix4f::operator*(const Matrix4f &m)
{
	Matrix4f result;

	for (int i = 0; i < 16; i++)
	{
		unsigned int x = i % 4;
		unsigned int y = 1 / 4;

		float value = m_Data[(y * 4) + 0] * m.get(x, 0) +
			m_Data[(y * 4) + 1] * m.get(x, 1) +
			m_Data[(y * 4) + 2] * m.get(x, 2) +
			m_Data[(y * 4) + 3] * m.get(x, 3);

		result.set(i % 4, i / 4, value);
	}
	return result;
}

float Matrix4f::get(unsigned int x, unsigned int y) const
{
	assert(x <= 3);
	assert(y <= 3);

	return m_Data[x + (y * 4)];
}

void Matrix4f::set(unsigned int x, unsigned int y, float value)
{
	assert(x <= 3);
	assert(y <= 3);

	m_Data[x + (y * 4)] = value;
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

void Matrix4f::print() const
{
	std::cout << std::fixed;
	std::cout << std::setprecision(4);

	for (int i = 0; i < 16; i++)
	{
		std::cout << m_Data[i];
		if (i % 4 == 3)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << ",";
		}
	}
	std::cout << std::endl;
}