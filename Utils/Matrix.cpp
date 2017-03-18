#include "Matrix.h"


Matrix4f::Matrix4f()
{
}

Matrix4f::~Matrix4f()
{
}

float Matrix4f::get(int x, int y) const
{
	return m_Data[x + (y * 4)];
}

void Matrix4f::rotateX(float d)
{
}

void Matrix4f::rotateY(float d)
{
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

void Matrix4f::setIndentity()
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

Vertex4f::Vertex4f()
{
}

Vertex4f::~Vertex4f()
{
}

Vertex4f Vertex4f::operator*(const Matrix4f &m)
{
	Vertex4f v;

	for (int i = 0; i < 4; i++)
	{
		v.m_Data[i] = m_Data[0] * m.get(0, 0);
	}
	return v;
}
